#include "IO.h"

void parse_project_data_file(ProjectMetaData* const projectMetaDataPtr) {

	int i = 0;
	FILE *input = fopen(file_path, "r");

	if (input == NULL) {
		printf("%d - parse_project_data_file :: IO.cpp\n", __LINE__);
		system("PAUSE");
		exit(0);
	}

	fscanf(input, "%d %d %f %f %d %f",
		&(projectMetaDataPtr->N),
		&(projectMetaDataPtr->K),
		&(projectMetaDataPtr->T),
		&(projectMetaDataPtr->dT),
		&(projectMetaDataPtr->LIMIT),
		&(projectMetaDataPtr->QM));

	/*check for malloc NULLs*/
	(projectMetaDataPtr->X) = (float*)malloc(sizeof(float)*(projectMetaDataPtr->N));
	(projectMetaDataPtr->Y) = (float*)malloc(sizeof(float)*(projectMetaDataPtr->N));
	(projectMetaDataPtr->Vx) = (float*)malloc(sizeof(float)*(projectMetaDataPtr->N));
	(projectMetaDataPtr->Vy) = (float*)malloc(sizeof(float)*(projectMetaDataPtr->N));

	while (!feof(input))
	{
		fscanf(input, "%f %f %f %f",
			&((projectMetaDataPtr->X)[i]),
			&((projectMetaDataPtr->Y)[i]),
			&((projectMetaDataPtr->Vx)[i]),
			&((projectMetaDataPtr->Vy)[i]));
		++i;
	}
	fclose(input);
}

void write_res_to_file(const float t, const float q, const Centroid* const centroids, const int centroids_size) {

	FILE *output = fopen(final_result_file_path, "w");

	fprintf(output, "First occurrence at t = %f with q = %f\n", t, q);

	for (int i = 0; i < centroids_size; i++)
	{
		fprintf(output, "C%d  (%f, %f)\n", i + 1, centroids[i].x, centroids[i].y);
	}
	fclose(output);
}

void write_qm_not_found_to_file() {
	FILE *output = fopen(final_result_file_path, "w");
	fprintf(output, "No QM found for this input file\n");
	fclose(output);
}