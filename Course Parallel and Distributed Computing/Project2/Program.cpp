#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <omp.h>
#include <mpi.h>

#include "IO.h"
#include "MyStructs.h"
#include "Kernel.h"
#include "Program.h"


// #define DEBUG_WRITE_TO_FILE
// #define WRITE_RESULT_TO_FILE
// #define CHECK_QM

int main(int argc, char *argv[]) {

	int rank, numprocs, root = 0;
	double t1 = -1, t2 = -1;
	ProjectMetaData projectMetaData;
	Point* points = NULL;
	NumberOfClustersSet numberOfClustersSet;
	NumberOfClustersSet* numberOfClustersSetArray = NULL;

	MPI_Datatype PointMPIType;
	MPI_Datatype ProjectDataMPIType;
	MPI_Datatype NumberOfClustersSetMPIType;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (numprocs > MAX_CLUSTERS - 1) {
		fprintf(stderr, "#numprocs>MAX_CLUSTERS-1#(%d)\n", __LINE__);
		MPI_Abort(MPI_COMM_WORLD, 0);
		exit(0);
	}

	points = (Point*)malloc(sizeof(Point)*MAX_POINTS);
	if (points == NULL) {
		fprintf(stderr, "#points = (Point*)malloc(sizeof(Point)*MAX_POINTS);#(%d)\n", __LINE__);
		MPI_Abort(MPI_COMM_WORLD, 1);
		exit(1);
	}

	if (rank == root) {
		t1 = omp_get_wtime();
		printf("#Program started#\n");
	}

	/*
	* create needed types to be used in MPI functions
	* */
	createTypes1(&PointMPIType, &ProjectDataMPIType, &NumberOfClustersSetMPIType);

	/*
	* initial initialization by root
	* */
	if (rank == root) {

		/*
		* root reads and parses project data file
		*/
		parse_project_data_file(&projectMetaData, &points);

		//DEBUG
		//printf("%d %d %d %d %.2f\n", projectMetaData.num_of_points, projectMetaData.vector_size, projectMetaData.max_clusters, projectMetaData.maxIter, projectMetaData.qm);


		/*
		* create the array to be scattered to all participating nodes
		* the array will contain int numbers where each number is how many clusters to look for
		*
		* Logic Notice:
		* its important that the possible number of clusters will be divided correctly, example:
		*
		* possible numbers of clusters: 2,3,4,5,6,7,8,9,10,11,12,13,14,15 | max_clusters=15
		* we have 3 nodes participating(including root) than the division is:
		* rank_0: 2,5,8,11,14 | array size = 5
		* rank_1: 3,6,9,12,15 | array size = 5
		* rank_2: 4,7,10,13   | array size = 4
		*
		* this division emerges because the nodes are synced! for each number of clusters
		* in the synchronization point the calculated quality of all!! nodes is checked
		* so if rank_0 worked on qm for 2, rank_1 must work on qm for 3! etc
		* other wise the program will may give false answers e.g:
		* if rank_0 would do 2 and rank_1 would do 15....when synced, the root may deduce that the qm for 15
		* is acceptable, stop the program and show the results for 15!!, in that case we didnt check for 3,4,5 etc!
		* that could yield an acceptable qm and in fact be the right answer according to project algo!
		* */
		numberOfClustersSetArray = (NumberOfClustersSet*)malloc(sizeof(NumberOfClustersSet) * numprocs);
		int numberOfClusters = 2;
		for (int j = 0; j < numprocs; ++j) {
			numberOfClustersSetArray[j].arraySize = 0;
		}

		//100-2+1 = 98 values for numbers of clusters i.e. max needed nodes when lunching MPICH is 99
		for (int i = 0; i < projectMetaData.max_clusters; ++i) {
			for (int j = 0; j < numprocs && numberOfClusters <= projectMetaData.max_clusters; ++j) {
				numberOfClustersSetArray[j].numberOfClustersSet[i] = numberOfClusters++;
				numberOfClustersSetArray[j].arraySize++;
			}
		}
	}


	/*
	* distribute project meta data to all participating nodes
	* distribute project points to all participating nodes
	* */
	MPI_Bcast(&projectMetaData, 1, ProjectDataMPIType, root, MPI_COMM_WORLD);
	MPI_Bcast(points, projectMetaData.num_of_points, PointMPIType, root, MPI_COMM_WORLD);

	/*
	* distribute to all participating nodes their set of num of clusters to calc
	* free numberOfClustersSetArray, that is not needed any more
	* */
	MPI_Scatter(numberOfClustersSetArray, 1, NumberOfClustersSetMPIType, &numberOfClustersSet, 1, NumberOfClustersSetMPIType, root, MPI_COMM_WORLD);
	if (rank == root) {
		free(numberOfClustersSetArray);
	}

	/*
	* start project procedure in parallel(SPMD)
	* */
	start_project_procedure(root, numprocs, rank, &projectMetaData, points, &numberOfClustersSet);

	/*
	* to be used only to get correct runtime otherwise redundent!
	* */
	MPI_Barrier(MPI_COMM_WORLD);

	if (rank == root) {
		t2 = omp_get_wtime();
		printf("#RUN-TIME# : %.3f sec\n", (t2 - t1));
	}

	MPI_Finalize();
	return 0;
}

void createTypes1(MPI_Datatype* PointMPITypePtr, MPI_Datatype* ProjectDataMPITypePtr, MPI_Datatype* NumberOfClustersSetMPITypePtr) {

	//Point creation
	//----------------------------------------------------------
	Point point;
	MPI_Datatype point_type[4] = { MPI_FLOAT, MPI_FLOAT, MPI_INT, MPI_INT };
	int point_blocklen[4] = { VEC_SIZE, 1, 1, 1 };
	MPI_Aint point_disp[4];

	point_disp[0] = (char *)&point.vector - (char *)&point;
	point_disp[1] = (char *)&point.minDis - (char *)&point;
	point_disp[2] = (char *)&point.myCentroidIndex - (char *)&point;
	point_disp[3] = (char *)&point.isDummyPoint - (char *)&point;
	MPI_Type_create_struct(4, point_blocklen, point_disp, point_type, PointMPITypePtr);
	MPI_Type_commit(PointMPITypePtr);
	//----------------------------------------------------------

	//ProjectData creation
	//----------------------------------------------------------
	ProjectMetaData projectMetaData;
	MPI_Datatype projectMetaData_type[5] = { MPI_INT, MPI_INT, MPI_INT, MPI_INT, MPI_FLOAT };
	int projectMetaData_blocklen[5] = { 1, 1, 1, 1, 1 };
	MPI_Aint projectMetaData_disp[5];

	projectMetaData_disp[0] = (char *)&projectMetaData.num_of_points - (char *)&projectMetaData;
	projectMetaData_disp[1] = (char *)&projectMetaData.vector_size - (char *)&projectMetaData;
	projectMetaData_disp[2] = (char *)&projectMetaData.max_clusters - (char *)&projectMetaData;
	projectMetaData_disp[3] = (char *)&projectMetaData.maxIter - (char *)&projectMetaData;
	projectMetaData_disp[4] = (char *)&projectMetaData.qm - (char *)&projectMetaData;
	MPI_Type_create_struct(5, projectMetaData_blocklen, projectMetaData_disp, projectMetaData_type, ProjectDataMPITypePtr);
	MPI_Type_commit(ProjectDataMPITypePtr);
	//----------------------------------------------------------

	//CentroidsSizeSet creation
	//----------------------------------------------------------
	NumberOfClustersSet numberOfClustersSet;
	MPI_Datatype numberOfClustersSet_type[2] = { MPI_INT, MPI_INT };
	int numberOfClustersSet_blocklen[2] = { MAX_CLUSTERS, 1 };
	MPI_Aint numberOfClustersSet_disp[2];

	numberOfClustersSet_disp[0] = (char *)&numberOfClustersSet.numberOfClustersSet - (char *)&numberOfClustersSet;
	numberOfClustersSet_disp[1] = (char *)&numberOfClustersSet.arraySize
		- (char *)&numberOfClustersSet;

	MPI_Type_create_struct(2, numberOfClustersSet_blocklen, numberOfClustersSet_disp, numberOfClustersSet_type, NumberOfClustersSetMPITypePtr);
	MPI_Type_commit(NumberOfClustersSetMPITypePtr);
	//----------------------------------------------------------
}

void createTypes2(MPI_Datatype* SyncedAnswerMPITypePtr) {

	//Centroid creation
	//----------------------------------------------------------
	Centroid centroid;
	MPI_Datatype CentroidMPIType;
	MPI_Datatype centroid_type[1] = { MPI_FLOAT };
	int centroid_blocklen[1] = { VEC_SIZE };
	MPI_Aint centroid_disp[1];

	centroid_disp[0] = (char *)&centroid.vector - (char *)&centroid;
	MPI_Type_create_struct(1, centroid_blocklen, centroid_disp, centroid_type, &CentroidMPIType);
	MPI_Type_commit(&CentroidMPIType);
	//---------------------------------------------------------

	//SyncedAnswer creation
	//----------------------------------------------------------
	SyncedAnswer syncedAnswer;
	MPI_Datatype syncedAnswer_type[4] = { CentroidMPIType, MPI_INT, MPI_INT, MPI_FLOAT };
	int syncedAnswer_blocklen[4] = { MAX_CLUSTERS, 1, 1, 1 };
	MPI_Aint syncedAnswer_disp[4];

	syncedAnswer_disp[0] = (char *)&syncedAnswer.centroids - (char *)&syncedAnswer;
	syncedAnswer_disp[1] = (char *)&syncedAnswer.arraySize - (char *)&syncedAnswer;
	syncedAnswer_disp[2] = (char *)&syncedAnswer.notSyncedAnyMore - (char *)&syncedAnswer;
	syncedAnswer_disp[3] = (char *)&syncedAnswer.qm - (char *)&syncedAnswer;
	MPI_Type_create_struct(4, syncedAnswer_blocklen, syncedAnswer_disp, syncedAnswer_type, SyncedAnswerMPITypePtr);
	MPI_Type_commit(SyncedAnswerMPITypePtr);
	//----------------------------------------------------------
}

void start_project_procedure(
	const int root,
	const int numprocs,
	const int rank,
	ProjectMetaData* const projectMetaDataPtr, 
	Point* pointsPtr,
	const NumberOfClustersSet* const numberOfClustersSetPtr) {

	SyncedAnswer* syncedAnswerArray = NULL;// for root to use
	SyncedAnswer syncedAnswer;// for all nodes to use
	MPI_Datatype SyncedAnswerMPIType;
	int canILeave = 0;// bool like var
	
	Centroid *centroids = NULL;
	int num_of_centroids = -1;
	float q = -1;
	int i = 0;
	
	// set points for CUDA optimization
	set_points_to_work_with_cuda(&pointsPtr, &projectMetaDataPtr->num_of_points);

	float* meta_centroids_sum = (float*)malloc(sizeof(float) * projectMetaDataPtr->max_clusters * projectMetaDataPtr->vector_size);
	int* meta_centroids_num_of_memebrs = (int*)malloc(sizeof(int) * projectMetaDataPtr->max_clusters);

	/*
	* a data structure that is used to calc dist between cluster for each qm calc
	*/
	float* meta_centroids_qualityEval = (float*)malloc(sizeof(float) * projectMetaDataPtr->max_clusters * projectMetaDataPtr->max_clusters);

	/*
	* to save the points for each cluster for each qm calc
	*/
	Point* cluster_points_qualityEval = (Point*)malloc(sizeof(Point)*projectMetaDataPtr->num_of_points);

	/*
	* to save diamters for each qm calc
	* for each cluster there will be one diameter
	*/
	float* diameters_qualityEval = (float*)malloc(sizeof(float)*projectMetaDataPtr->max_clusters);

	/*
	* 
	*/
	createTypes2(&SyncedAnswerMPIType);

	if (rank == 0) {
		syncedAnswerArray = (SyncedAnswer*)malloc(sizeof(SyncedAnswer)*numprocs);
	}

	while (!canILeave) {

		if (i < (numberOfClustersSetPtr->arraySize)) {
			
			num_of_centroids = (numberOfClustersSetPtr->numberOfClustersSet[i]);
			
			set_centroids(&centroids, num_of_centroids, pointsPtr, projectMetaDataPtr->vector_size);

			kmean(pointsPtr, projectMetaDataPtr->num_of_points,
				centroids, num_of_centroids,
				projectMetaDataPtr->vector_size,
				projectMetaDataPtr->maxIter,
				meta_centroids_sum,
				meta_centroids_num_of_memebrs);

			q = evaluateQuality(
				pointsPtr, projectMetaDataPtr->num_of_points,
				centroids, num_of_centroids,
				projectMetaDataPtr->vector_size,
				meta_centroids_num_of_memebrs,
				meta_centroids_qualityEval,
				cluster_points_qualityEval,
				diameters_qualityEval
			);

			++i;

			/*
			* set SyncedAnswer struct to be sent to root
			* */
			memcpy(syncedAnswer.centroids, centroids, sizeof(Centroid)*num_of_centroids);
			syncedAnswer.arraySize = num_of_centroids;
			syncedAnswer.notSyncedAnyMore = 0;// meaning still synced
			syncedAnswer.qm = q;
		}
		else if (i == (numberOfClustersSetPtr->arraySize)) {
			/*
			* set SyncedAnswer struct to be sent to root
			* set this answer as depricated i.e. not synced any more
			* */
			syncedAnswer.notSyncedAnyMore = 1;
		}

		/*
		* MPI sync and check point
		*
		* if node is out of cluster numbers to calc it indicates so via the notSyncedAnyMore var in syncedAnswer, and root ignores such answers 
		* */
		MPI_Gather(&syncedAnswer, 1, SyncedAnswerMPIType, syncedAnswerArray, 1, SyncedAnswerMPIType, root, MPI_COMM_WORLD);

		/*
		* root makes the qm check and sets: canILeave var
		* if the program has finished print the result
		*/
		if (rank == root) {
			
			for (int i = 0; i < numprocs; i++)
			{
				if (syncedAnswerArray[i].notSyncedAnyMore == 0) {
					printf("q=%.2f ", syncedAnswerArray[i].qm);
					if (syncedAnswerArray[i].qm < projectMetaDataPtr->qm) {
						canILeave = 1;
					}
				}
			}
			printf("\n");
		}

		/*
		* root send answer
		* */
		MPI_Bcast(&canILeave, 1, MPI_INT, root, MPI_COMM_WORLD);
	
	}// main while, canILeave

	free(pointsPtr);
	free(centroids);
	free(meta_centroids_sum);
	free(meta_centroids_num_of_memebrs);
	free(meta_centroids_qualityEval);
	free(cluster_points_qualityEval);
	free(diameters_qualityEval);

	if (rank == 0) {
		free(syncedAnswerArray);
	}
}

void set_centroids(Centroid** centroids, const int num_of_centroids,
	Point* const points, const int vector_size) {

	static int i = -1;

	if ((*centroids == NULL)) {

		(*centroids) = (Centroid*)malloc(sizeof(Centroid) * num_of_centroids);

#pragma omp parallel for default(shared) private(i) schedule(static)
		for (i = 0; i < num_of_centroids; ++i) {
			memcpy((*centroids)[i].vector, points[i].vector,
				sizeof(float) * vector_size);
		}
	}
	else {
		//for those vectors who already been alloc, it will copy there address which is good!
		(*centroids) = (Centroid*)realloc((*centroids),
			sizeof(Centroid) * num_of_centroids);

#pragma omp parallel for default(shared) private(i) schedule(static)
		for (i = 0; i < num_of_centroids; ++i) {
			memcpy((*centroids)[i].vector, points[i].vector,
				sizeof(float) * vector_size);
		}
	}
}

void kmean(Point* points, const int num_of_points, Centroid* const centroids,
	const int num_of_centroids, const int vector_size,
	const int max_iterations, float* const meta_centroids_sum,
	int* const meta_centroids_num_of_memebrs) {

	int iterCtr = 0;
	static unsigned int needMoreIterToConverge;


	do {
		// set def to false each local round
		needMoreIterToConverge = 0;
		++iterCtr;

		// 1) classify points to centroids (CUDA)
		// for now dummy impl. with omp
		classify_points_by_norm(points, num_of_points, centroids,
			num_of_centroids, vector_size);

		// 2) for each cluster: sum its points and members (openMP)
		zero_meta_data_structures(num_of_centroids, vector_size,
			meta_centroids_sum, meta_centroids_num_of_memebrs);

		count_and_sum_after_classification_by_norm(points, num_of_points,
			num_of_centroids, vector_size, meta_centroids_sum,
			meta_centroids_num_of_memebrs);

		// 3) check if centroids changed (openMP)
		needMoreIterToConverge = check_centroids_for_changes(meta_centroids_sum,
			meta_centroids_num_of_memebrs, centroids, num_of_centroids,
			vector_size);

	} while ((iterCtr < max_iterations) && (needMoreIterToConverge));
}

void zero_meta_data_structures(const int num_of_centroids,
	const int vector_size, float* const meta_centroids_sum,
	int* const meta_centroids_num_of_memebrs) {

	int i, j;

	// using omp collapse(2), should increase performance, not available here!
#pragma omp parallel for default(shared) private(i, j)
	for (i = 0; i < num_of_centroids; i++) {
		for (j = 0; j < vector_size; j++) {
			meta_centroids_sum[i * vector_size + j] = 0;
		}
		meta_centroids_num_of_memebrs[i] = 0;//fixed bug, there was no assignment value!
	}
}

void count_and_sum_after_classification_by_norm(const Point * const points,
	const int num_of_points, const int num_of_centroids,
	const int vector_size, float* const meta_centroids_sum,
	int* const meta_centroids_num_of_memebrs) {

	int i, j, k;

	// found that doing extra work is still fatser then doing some kind of synchronization!
	// using omp collapse(2), should increase performance, not available here!
#pragma omp parallel for default(shared) private(i, j, k)
	for (i = 0; i < num_of_centroids; i++)
	{
		for (j = 0; j < num_of_points; j++)
		{
			if ((!points[j].isDummyPoint) && (points[j].myCentroidIndex == i))
			{
				for (k = 0; k < vector_size; k++)
				{
					meta_centroids_sum[i * vector_size + k] += points[j].vector[k];
				}
				++(meta_centroids_num_of_memebrs[i]);
			}
		}
	}
}

unsigned int check_centroids_for_changes(float* meta_centroids_sum,
	int* meta_centroids_num_of_memebrs, Centroid *centroids,
	const int num_of_centroids, const int vector_size) {

	int i, j;
	float* new_vector = NULL;
	unsigned int needMoreIterToConverge = 0;
	unsigned int* needMoreIterToConvergeArr = (unsigned int*)malloc(sizeof(unsigned int) * num_of_centroids);
	int cluster_size = 0;

#pragma omp parallel default(shared) private(i, j) firstprivate(new_vector, cluster_size)
	{
		//each has its own new_vector
		new_vector = (float*)malloc(sizeof(float) * vector_size);

		//each cpu will have its own index - i
#pragma omp for schedule(static)
		for (i = 0; i < num_of_centroids; i++)
		{
			needMoreIterToConvergeArr[i] = 0;
			cluster_size = meta_centroids_num_of_memebrs[i];
			if (cluster_size != 0)
			{
				//calc new centroid vector to temp var
				for (j = 0; j < vector_size; j++)
				{
					new_vector[j] = (meta_centroids_sum[i * vector_size + j] / cluster_size);
				}

				//check for changes with original
				for (j = 0; j < vector_size; j++)
				{
					if (new_vector[j] != centroids[i].vector[j])
					{
						needMoreIterToConvergeArr[i] = 1;
						break;
					}
				}

				//copy if there are changes
				if (needMoreIterToConvergeArr[i]) {
					memcpy(centroids[i].vector, new_vector, sizeof(float) * vector_size);
				}
			}
		}

#pragma omp for reduction(|| : needMoreIterToConverge)
		for (i = 0; i < num_of_centroids; i++) {
			needMoreIterToConverge = needMoreIterToConverge || needMoreIterToConvergeArr[i];
		}

		free(new_vector);
	}

	free(needMoreIterToConvergeArr);

	return needMoreIterToConverge;
}

float evaluateQuality(
	Point* const points, const int num_of_points,
	Centroid* const centroids, const int num_of_centroids,
	const int vector_size,
	const int* const meta_centroids_num_of_memebrs,
	float* const meta_centroids_qualityEval,
	Point* const cluster_points_qualityEval,
	float* const diameters_qualityEval) {

	calc_distances_between_centroids(centroids, num_of_centroids, meta_centroids_qualityEval, vector_size);

	calc_diameter_for_each_cluster(
		points, num_of_points,
		num_of_centroids,
		vector_size,
		meta_centroids_num_of_memebrs,
		cluster_points_qualityEval,
		diameters_qualityEval
	);

	// now we have all data, lets calc the qm and compare it
	float q = 0;
	float d;
	int number_of_elements_to_sum_in_q = -1;
	int j;

	for (int i = 0; i < num_of_centroids; ++i)
	{
		d = diameters_qualityEval[i];

		j = 0;
		while (j < num_of_centroids) {
			if (j != i)
			{
				if (meta_centroids_qualityEval[i*num_of_centroids + j] != -1)
				{
					q += (d / meta_centroids_qualityEval[i*num_of_centroids + j]);
				}
				else if (meta_centroids_qualityEval[i*num_of_centroids + j] == -1)
				{
					q += (d / meta_centroids_qualityEval[j*num_of_centroids + i]);
				}
			}
			++j;
		}
	}

	number_of_elements_to_sum_in_q = (num_of_centroids*(num_of_centroids - 1));

	q /= number_of_elements_to_sum_in_q;

	return q;
}

void calc_distances_between_centroids(
	const Centroid* const centroids, const int num_of_centroids,
	float* const centroids_distances,
	const int vector_size) {

	int i, j, k;
	float temp = 0;

#pragma omp parallel default(shared) private(i, j, k) firstprivate(temp)
	{
		//init distances matrix with immpossible value
#pragma omp for schedule(static)
		for (i = 0; i < num_of_centroids; i++) {
			for (j = 0; j < num_of_centroids; j++) {
				centroids_distances[i * num_of_centroids + j] = -1;
			}
		}

#pragma omp for schedule(static)
		for (i = 0; i < num_of_centroids; i++) {
			for (j = i + 1; j < num_of_centroids; j++) {
				for (k = 0; k < vector_size; k++) {
					temp += pow(centroids[i].vector[k] - centroids[j].vector[k], 2);
				}
				if (temp != 0)
				{
					centroids_distances[i * num_of_centroids + j] = sqrt(temp);
					temp = 0;
				}
			}
		}
	}
}

void calc_diameter_for_each_cluster(
	Point* const points, const int num_of_points,
	const int num_of_centroids,
	const int vector_size,
	const int* const meta_centroids_num_of_memebrs,
	Point* const cluster_points_qualityEval,
	float* const diameters_qualityEval
) {


	Point* buff_s = (Point*)malloc(sizeof(Point)*num_of_points);
	memcpy(buff_s, points, sizeof(Point)*num_of_points);

	// sort points by cluster id
	qsort(buff_s, num_of_points, sizeof(Point), sortPointsByCentroidIndex);
	//qsort(points, num_of_points, sizeof(Point), sortPointsByCentroidIndex);

	// for each cluster calc its diamter
	//Point* curr_start = points; // init
	Point* curr_start = buff_s;

	//Point* points_end_ptr = points + num_of_points;
	Point* points_end_ptr = buff_s + num_of_points;

	int jump = 0;
	int size = -1;
	float max = 0;
	int i, j, k, v;
	float temp = 0;

	for (v = 0; v < num_of_centroids; ++v)
	{
		//copy chunk for omp to work with
		size = meta_centroids_num_of_memebrs[v];

		if (size >= 2) {

			memcpy(cluster_points_qualityEval, curr_start, sizeof(Point)*size);

			//omp part
#pragma omp parallel for default(shared) private(i, j, k) firstprivate(temp) schedule(static)
			for (i = 0; i < size; ++i)
			{
				for (j = i + 1; j < size; ++j)
				{
					for (k = 0; k < vector_size; ++k)
					{
						temp += pow(cluster_points_qualityEval[i].vector[k] - cluster_points_qualityEval[j].vector[k], 2);
					}
					temp = sqrt(temp);
#pragma omp critical
					{
						if (max < temp) {
							max = temp;
						}
					}
					temp = 0;
				}
			}
			diameters_qualityEval[v] = max;
		}
		else {
			diameters_qualityEval[v] = 0;
		}

		max = 0;

		//set jump
		jump = size; // meta_centroids_num_of_memebrs[v];
					 //set the pointer to the start of the wanted points chunk
		curr_start += jump;
	}

	free(buff_s);

}

int sortPointsByCentroidIndex(const void* p1, const void* p2) {

	int l = ((Point*)p1)->myCentroidIndex;
	int r = ((Point*)p2)->myCentroidIndex;
	return (l - r);
}
