#ifndef SRC_GUI_VIEWER_H_
#define SRC_GUI_VIEWER_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    unsigned *vertexes;
    unsigned numbers_of_vertexes_in_facets;
} facets_t;

typedef struct {
    double **matrix;
    unsigned rows;
    unsigned cols;
} matrix_t;

typedef struct {
    unsigned vertex_cnt;
    unsigned facet_cnt;
    double *dst;
    unsigned *polyg;
    matrix_t matrix3d;
    facets_t *polygons;
} data_t;

int count_of_vertexes(FILE *one, data_t *obj);
void fill_matrix(data_t *obj, FILE *one);
void skip_spaces(FILE* one);
int cnt_verts_in_facet(char *src);
void fill_facet_array(data_t *obj, char *src, int index_pol);
void polyg_array(data_t *obj);
void from_matr_to_array(data_t *obj);
void move_z(data_t *obj, double offset);
void move_y(data_t *obj, double offset);
void move_x(data_t *obj, double offset);
void rotation_by_ox(data_t *obj, double angle);
void zoom(data_t *obj, double k);
void rotation_by_oz(data_t *obj, double angle);
void rotation_by_oy(data_t *obj, double angle);

#endif  // SRC_GUI_VIEWER_H_
