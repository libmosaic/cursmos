#include "cursmos_stream_io.h"

int fgetCURS_MOS (CURS_MOS *target, FILE *stream) {
	// get the MOSAIC, please
	int aux = fgetMOSAIC (target->img, stream);

	if (aux == 0 || aux == EUNKNSTRGFMT) {
		// resize only target's WINDOW, as the MOSAIC was resized on fgetMOSAIC
		ResizeCURS_MOS_WINDOW (target, target->img->height, target->img->width);
		// refreshing
		RewriteCURS_MOS (target);
	}

	return aux;
}


int LoadCURS_MOS (CURS_MOS *target, const char *file_name) {
	// load the MOSAIC, please
	int aux = LoadMOSAIC (target->img, file_name);

	if (aux == 0 || aux == EUNKNSTRGFMT) {
		// resize only target's WINDOW, as the MOSAIC was resized on LoadMOSAIC
		ResizeCURS_MOS_WINDOW (target, target->img->height, target->img->width);
		// refreshing
		RewriteCURS_MOS (target);
	}

	return aux;
}


int SaveIMGS (IMGS *imgs, const char *file_name) {
	FILE *f;
	if ((f = fopen (file_name, "w")) == NULL) {
		return errno;
	}

	int i, ret = 0;
	CURS_MOS *aux;
	for (i = 0, aux = imgs->list; i < imgs->size; i++, aux = aux->next) {
		ret = fputCURS_MOS (aux, f);
		if (ret == ERR) {
			break;
		}
	}

	fclose (f);

	return ret;
}


int LoadIMGS (IMGS *imgs, const char *file_name) {
	FILE *f;
	if ((f = fopen (file_name, "r")) == NULL) {
		return errno;
	}
	
	int ret;
	CURS_MOS *new_image;

	// first CURS_MOS
	new_image = NewCURS_MOS (0, 0);
	ret = fgetCURS_MOS (new_image, f);
	if (ret != 0 && ret != EUNKNSTRGFMT) {
		fclose (f);
		return ERR;
	}
	CircularIMGS (imgs, new_image);

	// and the others
	while (1) {
		new_image = NewCURS_MOS (0, 0);
		ret = fgetCURS_MOS (new_image, f);
		if (ret != 0 && ret != EUNKNSTRGFMT) {
			break;
		}
		LinkCURS_MOS (imgs->list->prev, new_image, after);
	}

	fclose (f);

	return 0;
}
