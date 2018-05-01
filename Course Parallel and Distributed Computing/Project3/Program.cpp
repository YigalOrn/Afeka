#include "Program.h"

int main(int argc, char* argv[])
{
	int rank, numprocs;
	double t1 = -1, t2 = -1;

	ProjectMetaData projectMetaData;
	TimeData timeData;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/*
	* - calc needed meta data by root for distribution
	* - arrange data by root for MPI distribution
	* - send data to each node
	*/
	if (rank == ROOT) {
		// set start time
		t1 = omp_get_wtime();
		printf("#Program started#\n");
		fflush(stdout);

		parse_project_data_file(&projectMetaData);
		/*
		* for SyncedAnswer Struct and MPI serialization when each node has calc its q for round t
		*/
		if (projectMetaData.K > MAX_CLUSTERS) {
			printf("@ go to MyStructs.h and change to: MAX_CLUSTERS >= K , and then run again @\n");
			fflush(stdout);
			system("PAUSE");
			exit(0);
		}
		printf("#project data input file parsed#\n");
		fflush(stdout);
		stamp_count_time(&t1);

		printf("#root distributes meta data#\n");
		fflush(stdout);
		send_meta_data(numprocs, &projectMetaData, &timeData);
		printf("#root done distributes meta data#\n");
		fflush(stdout);
		stamp_count_time(&t1);
	}
	/*
	* - receive data from root
	*/
	else {
		recv_meta_data(&projectMetaData, &timeData);
	}

	start_project_task(rank, numprocs, &projectMetaData, &timeData);

	/*
	* free allocated data for all nodes
	*/
	free_node_meta_data(&projectMetaData, &timeData);

	/*
	* to be used only to get correct runtime otherwise redundant!
	*/
	//MPI_Barrier(MPI_COMM_WORLD);
	if (rank == ROOT) {
		printf("#DONE#\n");
		fflush(stdout);
		// set stop time
		stamp_count_time(&t1);
	}

	MPI_Finalize();
	return 0;
}

void free_node_meta_data(ProjectMetaData* projectMetaDataPtr, TimeData* timeDataPtr) {
	free(projectMetaDataPtr->X);
	free(projectMetaDataPtr->Y);
	free(projectMetaDataPtr->Vx);
	free(projectMetaDataPtr->Vy);
	free(timeDataPtr->time_array);
}

void stamp_count_time(const double* const t1Ptr) {
	double t2 = omp_get_wtime();
	printf("#RUN-TIME# : %.3f sec\n", (t2 - *t1Ptr));
	fflush(stdout);
}

void send_meta_data(
	const int numprocs,
	ProjectMetaData* const projectMetaDataPtr,
	TimeData* const timeDataPtr) {

	int i = -1;
	TimeData* timeDataArray = (TimeData*)malloc(sizeof(TimeData)*numprocs);

	calc_time_arrays(projectMetaDataPtr, timeDataArray, numprocs);

	/*
	* set roots time array;
	*/
	timeDataPtr->arraySize = timeDataArray[0].arraySize;
	timeDataPtr->time_array = (float*)malloc(sizeof(float)*(timeDataPtr->arraySize));
	memcpy(timeDataPtr->time_array, timeDataArray[0].time_array, sizeof(float)*(timeDataPtr->arraySize));

	for (i = 0; i < numprocs; ++i)
	{
		if (i != ROOT)
		{
			int byte_buffer_size = (sizeof(int) * 3) +
				(sizeof(float) * 3) +
				(sizeof(float) * 4 * (projectMetaDataPtr->N)) +
				sizeof(int) +
				(sizeof(float)*timeDataArray[i].arraySize);

			char* byte_buffer = (char*)malloc(sizeof(char)*byte_buffer_size);
			assert(byte_buffer != NULL);
			int pos = 0;

			MPI_Pack(&(projectMetaDataPtr->N), 1, MPI_INT, byte_buffer, byte_buffer_size, &pos, MPI_COMM_WORLD);
			MPI_Pack(&(projectMetaDataPtr->K), 1, MPI_INT, byte_buffer, byte_buffer_size, &pos, MPI_COMM_WORLD);
			MPI_Pack(&(projectMetaDataPtr->LIMIT), 1, MPI_INT, byte_buffer, byte_buffer_size, &pos, MPI_COMM_WORLD);
			MPI_Pack(&(projectMetaDataPtr->QM), 1, MPI_FLOAT, byte_buffer, byte_buffer_size, &pos, MPI_COMM_WORLD);
			MPI_Pack(&(projectMetaDataPtr->T), 1, MPI_FLOAT, byte_buffer, byte_buffer_size, &pos, MPI_COMM_WORLD);
			MPI_Pack(&(projectMetaDataPtr->dT), 1, MPI_FLOAT, byte_buffer, byte_buffer_size, &pos, MPI_COMM_WORLD);

			MPI_Pack(projectMetaDataPtr->X, projectMetaDataPtr->N, MPI_FLOAT, byte_buffer, byte_buffer_size, &pos, MPI_COMM_WORLD);
			MPI_Pack(projectMetaDataPtr->Y, projectMetaDataPtr->N, MPI_FLOAT, byte_buffer, byte_buffer_size, &pos, MPI_COMM_WORLD);
			MPI_Pack(projectMetaDataPtr->Vx, projectMetaDataPtr->N, MPI_FLOAT, byte_buffer, byte_buffer_size, &pos, MPI_COMM_WORLD);
			MPI_Pack(projectMetaDataPtr->Vy, projectMetaDataPtr->N, MPI_FLOAT, byte_buffer, byte_buffer_size, &pos, MPI_COMM_WORLD);

			MPI_Pack(&(timeDataArray[i].arraySize), 1, MPI_INT, byte_buffer, byte_buffer_size, &pos, MPI_COMM_WORLD);
			MPI_Pack(timeDataArray[i].time_array, timeDataArray[i].arraySize, MPI_FLOAT, byte_buffer, byte_buffer_size, &pos, MPI_COMM_WORLD);

			MPI_Send(byte_buffer, pos, MPI_PACKED, i, 0, MPI_COMM_WORLD);

			free(byte_buffer);
		}
	}

#pragma omp parallel for default(shared) private(i) schedule(static)
	for (i = 0; i < numprocs; ++i)
	{
		free(timeDataArray[i].time_array);
	}
	free(timeDataArray);
}

void recv_meta_data(ProjectMetaData* const projectMetaDataPtr, TimeData* const timeDataPtr) {
	int byte_buffer_size = -1;
	int pos = 0;

	MPI_Status status;

	MPI_Probe(ROOT, 0, MPI_COMM_WORLD, &status);
	MPI_Get_count(&status, MPI_BYTE, &byte_buffer_size);

	char* byte_buffer = (char*)malloc(sizeof(char)*byte_buffer_size);
	MPI_Recv(byte_buffer, byte_buffer_size, MPI_PACKED, ROOT, 0, MPI_COMM_WORLD, &status);

	MPI_Unpack(byte_buffer, byte_buffer_size, &pos, &(projectMetaDataPtr->N), 1, MPI_INT, MPI_COMM_WORLD);
	MPI_Unpack(byte_buffer, byte_buffer_size, &pos, &(projectMetaDataPtr->K), 1, MPI_INT, MPI_COMM_WORLD);
	MPI_Unpack(byte_buffer, byte_buffer_size, &pos, &(projectMetaDataPtr->LIMIT), 1, MPI_INT, MPI_COMM_WORLD);
	MPI_Unpack(byte_buffer, byte_buffer_size, &pos, &(projectMetaDataPtr->QM), 1, MPI_FLOAT, MPI_COMM_WORLD);
	MPI_Unpack(byte_buffer, byte_buffer_size, &pos, &(projectMetaDataPtr->T), 1, MPI_FLOAT, MPI_COMM_WORLD);
	MPI_Unpack(byte_buffer, byte_buffer_size, &pos, &(projectMetaDataPtr->dT), 1, MPI_FLOAT, MPI_COMM_WORLD);

	projectMetaDataPtr->X = (float*)malloc(sizeof(float)*projectMetaDataPtr->N);
	projectMetaDataPtr->Y = (float*)malloc(sizeof(float)*projectMetaDataPtr->N);
	projectMetaDataPtr->Vx = (float*)malloc(sizeof(float)*projectMetaDataPtr->N);
	projectMetaDataPtr->Vy = (float*)malloc(sizeof(float)*projectMetaDataPtr->N);

	MPI_Unpack(byte_buffer, byte_buffer_size, &pos, projectMetaDataPtr->X, projectMetaDataPtr->N, MPI_FLOAT, MPI_COMM_WORLD);
	MPI_Unpack(byte_buffer, byte_buffer_size, &pos, projectMetaDataPtr->Y, projectMetaDataPtr->N, MPI_FLOAT, MPI_COMM_WORLD);
	MPI_Unpack(byte_buffer, byte_buffer_size, &pos, projectMetaDataPtr->Vx, projectMetaDataPtr->N, MPI_FLOAT, MPI_COMM_WORLD);
	MPI_Unpack(byte_buffer, byte_buffer_size, &pos, projectMetaDataPtr->Vy, projectMetaDataPtr->N, MPI_FLOAT, MPI_COMM_WORLD);

	MPI_Unpack(byte_buffer, byte_buffer_size, &pos, &(timeDataPtr->arraySize), 1, MPI_INT, MPI_COMM_WORLD);
	timeDataPtr->time_array = (float*)malloc(sizeof(float)*(timeDataPtr->arraySize));
	MPI_Unpack(byte_buffer, byte_buffer_size, &pos, timeDataPtr->time_array, timeDataPtr->arraySize, MPI_FLOAT, MPI_COMM_WORLD);

	free(byte_buffer);
}

void calc_time_arrays(
	const ProjectMetaData* const projectMetaData,
	TimeData* const timeDataArray,
	const int numprocs)
{
	int i = -1, j = -1;
	int timeArraySize = (int)((projectMetaData->T / projectMetaData->dT) + 1);
	float *timeArray = (float*)malloc(sizeof(float)*timeArraySize);

#pragma omp parallel default(shared) private(i) 
	{
		// calc times
#pragma omp for schedule(static)
		for (i = 0; i < timeArraySize; ++i)
		{
			timeArray[i] = (projectMetaData->dT)*i;
		}

		// alloc a time array for each node
#pragma omp for schedule(static)
		for (i = 0; i < numprocs; ++i)
		{
			timeDataArray[i].time_array = (float*)malloc(sizeof(float)*timeArraySize);
			timeDataArray[i].arraySize = 0;
		}
	}

	/*
	* under lying assumption is that the times array is evenly divided as
	* possible in regard to the numprocs
	*
	* should be serial, parallelizm can be done with openmp version 3.0 and upper,
	* the for pragma can be set that not only the outer for is divided but also the inner for!
	* in that case no need to sync critical areas of code for the wanted logic!
	*
	* time in interval dT are divided among nodes consecutively !!!
	* e.g:
	* times = [0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1]
	* numprocs = 3
	* rank 0 : 0,   0.3....
	* rank 1 : 0.1, 0.4....
	* rank 2 : 0.2, 0.5....
	*
	* this division is critical for the proposed design where the nodes sync their answers after
	* finishing k-means and calc the qm for that round, because of the sync we want
	* each node to work on consecutive times! so the first qm that is less then QM is found.
	*/
	for (i = 0; i < timeArraySize; i += numprocs)
	{
		for (j = 0; j < numprocs; ++j)
		{
			if (i + j < timeArraySize)
			{
				timeDataArray[j].time_array[timeDataArray[j].arraySize++] = timeArray[i + j];
			}
		}
	}

	free(timeArray);
}

void start_project_task(
	const int rank,
	const int numprocs,
	ProjectMetaData* projectMetaDataPtr,
	const TimeData* const timeDataPtr) {

	/*
	* init phase:
	* 1) set an array of points(that hold Point structs)
	*	1.1) use CUDA system gpu data to optimize CUDA work, get system gpu data
	*	1.2) calc needed points for CUDA
	*	1.3) add dummy points as needed to the points array(change points array size)
	* work phase:
	* while(root says cont)
	*	for each time in this node time array:
	*		1) init first N points, set the rest as dummy points
	*		2) set K first points as initial centroids
	*		3) calc centroids using K-mean algo
	*		4) calc qm for this time iter
	*		5) send qm with centroids and curr time (in a special struct that has synchronization bool indicator) to root
	*		6) get/wait for root permision to continue while loop
	*			- if work done exit for and while loop
	*			- else
	*				- node has more elements in time array to work with
	*				- done with the for loop, stays in while loop byt sends root unsynced answers
	* node job done phase:
	* 1) free allocated memory(check all above steps also freed mem as needed!!!!)
	*
	*/

	int notSyncedCtr = -1;
	SyncedAnswer* syncedAnswerArray = NULL;// for root to use
	if (rank == ROOT) {
		syncedAnswerArray = (SyncedAnswer*)malloc(sizeof(SyncedAnswer)*numprocs);
		notSyncedCtr = 0;
	}

	SyncedAnswer syncedAnswer;// for all nodes to use(including root as a node/slave)
	MPI_Datatype SyncedAnswerMPIType;// for MPI collective ops
	createType(&SyncedAnswerMPIType);


	float q = -1;
	int time_index = 0;
	const int  centroids_size = projectMetaDataPtr->K;
	int points_size = projectMetaDataPtr->N;
	int canILeave = 0;
	Centroid* centroids = (Centroid*)malloc(sizeof(Centroid)*(centroids_size));
	Point * points = create_empty_points_array(projectMetaDataPtr);

	set_points_to_work_with_cuda(&points, &points_size);


	// for K-means
	unsigned int* need_more_iter_to_converge_arr = NULL;
	float* centroids_x_sum = NULL;
	float* centroids_y_sum = NULL;
	int* centroids_num_of_members = NULL;

	alloc_k_means_meta_data_structures(centroids_size, &need_more_iter_to_converge_arr, &centroids_x_sum, &centroids_y_sum, &centroids_num_of_members);

	// for QM
	float* centroids_dists_mat = NULL;
	float* centroids_diameters_arr = NULL;
	Point* cluster_points = NULL;// for diameter calc

	alloc_QM_meta_data_structures(points_size, centroids_size, &centroids_dists_mat, &centroids_diameters_arr, &cluster_points);


	while (!canILeave) {

		if (time_index < timeDataPtr->arraySize) {
			
			init_points_and_centroids_for_this_time_round(projectMetaDataPtr, points, points_size, centroids, centroids_size, timeDataPtr->time_array[time_index]);

			// kmean
			// after finish: centroids and points hold the changed data for this time iteration
			// if needed we also have the last meta_data_structures
			k_means(rank,
				projectMetaDataPtr->K, projectMetaDataPtr->LIMIT,
				points, points_size, centroids, centroids_size,
				need_more_iter_to_converge_arr,
				centroids_x_sum, centroids_y_sum, centroids_num_of_members);

			// find qm for kmean final results for this time iter
			q = evaluateQuality(
				points, points_size,
				centroids, centroids_size,
				centroids_num_of_members,
				centroids_dists_mat,
				centroids_diameters_arr,
				cluster_points);


#ifdef DEBUG_1
			printf("rank:%d, t:%f, q:%f\n", rank, timeDataPtr->time_array[time_index], q);
			fflush(stdout);
#endif
			
			// set SyncedAnswer struct to be sent to root
			memcpy(syncedAnswer.centroids, centroids, sizeof(Centroid)*centroids_size);
			syncedAnswer.arraySize = centroids_size;
			syncedAnswer.notSyncedAnyMore = 0;// meaning still synced
			syncedAnswer.qm = q;
			syncedAnswer.t = timeDataPtr->time_array[time_index];

			// after creating the answer we can increment time
			++time_index;

		}
		else {
			syncedAnswer.notSyncedAnyMore = 1;
		}

		// MPI sync and check point
		// if node is out of cluster numbers to calc it indicates so via the notSyncedAnyMore var in syncedAnswer, and root ignores such answers
		MPI_Gather(&syncedAnswer, 1, SyncedAnswerMPIType, syncedAnswerArray, 1, SyncedAnswerMPIType, ROOT, MPI_COMM_WORLD);

		// root makes the qm check and sets: canILeave var
		// if the program has finished print the result
		if (rank == ROOT) {
			for (int i = 0; i < numprocs; i++)
			{
				/*
				* add a counter to root
				* root will check if number of unsynced answers is equal to numprocs:
				* 	- if so then, all nodes finished and no qualified qm was found,
				*	  exit while loop and write this to file
				*	- else, some nodes are still synced, proceed as usual 			
				*/
				if (syncedAnswerArray[i].notSyncedAnyMore == 0) {
					

#ifdef DEBUG_2
					printf("@ ROOT-CHECK, t=%f, q=%f @\n", syncedAnswerArray[i].t, syncedAnswerArray[i].qm);
					fflush(stdout);
#endif
								
					if (syncedAnswerArray[i].qm < projectMetaDataPtr->QM) {
#ifdef DEBUG_3
						printf("index: %d\n", i);
						fflush(stdout);
#endif

						write_res_to_file(syncedAnswerArray[i].t, syncedAnswerArray[i].qm, syncedAnswerArray[i].centroids, syncedAnswerArray[i].arraySize);
						canILeave = 1;
						break;
					}
				} 
				else {
					notSyncedCtr++;
				}
			}
			if(notSyncedCtr == numprocs) {
				/*
				* add this function to IO
				*/
				write_qm_not_found_to_file();
				canILeave = 1;
			}
			notSyncedCtr = 0 ;
		}

		// root sends answer back
		MPI_Bcast(&canILeave, 1, MPI_INT, ROOT, MPI_COMM_WORLD);

	}// while


	if (rank == ROOT) {
		free(syncedAnswerArray);
	}
	free(points);
	free(centroids);
	free_k_means_meta_data_structures(need_more_iter_to_converge_arr, centroids_x_sum, centroids_y_sum, centroids_num_of_members);
	free_QM_meta_data_structures(centroids_dists_mat, centroids_diameters_arr, cluster_points);
}

Point* create_empty_points_array(ProjectMetaData* projectMetaDataPtr) {
	Point* points = (Point*)malloc(sizeof(Point)*(projectMetaDataPtr->N));
	if (points == NULL) {
		printf("%d - createEmptyPointsArray :: Program.cpp\n", __LINE__);
		system("PAUSE");
		exit(0);
	}
	return points;
}

void init_points_and_centroids_for_this_time_round(
	const ProjectMetaData* const projectMetaDataPtr,
	Point *points, const int points_size,
	Centroid* centroids, const int centroids_size,
	const float t) {

	int i = -1;

#pragma omp parallel default(shared) private(i)
	{
		// init first N points, set as not dummy
#pragma omp for schedule(static)
		for (i = 0; i < projectMetaDataPtr->N; i++)
		{
			points[i].isDummyPoint = 0;// binary false
			points[i].x = projectMetaDataPtr->X[i] + t*projectMetaDataPtr->Vx[i];
			points[i].y = projectMetaDataPtr->Y[i] + t*projectMetaDataPtr->Vy[i];
			if (i < centroids_size) {
				centroids[i].my_index = i;
				centroids[i].x = points[i].x;
				centroids[i].y = points[i].y;
			}
		}

		// init the rest, set as dummy
		// if points_size == N then nothing wrong happens
#pragma omp for schedule(static)
		for (i = projectMetaDataPtr->N; i < points_size; i++)
		{
			points[i].isDummyPoint = 1;// binary false
			points[i].myCentroidIndex = projectMetaDataPtr->K + 1; ///<<<<<<<<--------------------------------------------- check for run
		}

	}
}

void createType(MPI_Datatype* SyncedAnswerMPITypePtr) {

	//Centroid creation
	//----------------------------------------------------------
	Centroid centroid;
	MPI_Datatype CentroidMPIType;
	MPI_Datatype centroid_type[3] = { MPI_FLOAT, MPI_FLOAT, MPI_INT };
	int centroid_blocklen[3] = { 1, 1, 1 };
	MPI_Aint centroid_disp[3];

	centroid_disp[0] = (char *)&centroid.x - (char *)&centroid;
	centroid_disp[1] = (char *)&centroid.y - (char *)&centroid;
	centroid_disp[2] = (char *)&centroid.my_index - (char *)&centroid;
	
	MPI_Type_create_struct(3, centroid_blocklen, centroid_disp, centroid_type, &CentroidMPIType);
	MPI_Type_commit(&CentroidMPIType);
	//---------------------------------------------------------

	//SyncedAnswer creation
	//----------------------------------------------------------
	SyncedAnswer syncedAnswer;
	MPI_Datatype syncedAnswer_type[5] = { CentroidMPIType, MPI_INT, MPI_INT, MPI_FLOAT, MPI_FLOAT };
	int syncedAnswer_blocklen[5] = { MAX_CLUSTERS, 1, 1, 1, 1 };
	MPI_Aint syncedAnswer_disp[5];

	syncedAnswer_disp[0] = (char *)&syncedAnswer.centroids - (char *)&syncedAnswer;
	syncedAnswer_disp[1] = (char *)&syncedAnswer.arraySize - (char *)&syncedAnswer;
	syncedAnswer_disp[2] = (char *)&syncedAnswer.notSyncedAnyMore - (char *)&syncedAnswer;
	syncedAnswer_disp[3] = (char *)&syncedAnswer.qm - (char *)&syncedAnswer;
	syncedAnswer_disp[4] = (char *)&syncedAnswer.t - (char *)&syncedAnswer;
	
	MPI_Type_create_struct(5, syncedAnswer_blocklen, syncedAnswer_disp, syncedAnswer_type, SyncedAnswerMPITypePtr);
	MPI_Type_commit(SyncedAnswerMPITypePtr);
	//----------------------------------------------------------
}


