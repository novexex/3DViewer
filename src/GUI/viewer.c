#include "viewer.h"

int count_of_vertexes(FILE *one, data_t *obj) {
    int c = 0;
    int prev = '\n';
    int prev2 = 0;
    int cnt_vertex = 0;
    int cnt_facet = 0;
    int res = 1;
    while ((c = fgetc(one)) != EOF) {
        if (prev == 'v' && prev2 == '\n' && c == ' ') {
            cnt_vertex++;
        }
        if (prev == 'f' && prev2 == '\n' && c == ' ')
            cnt_facet++;
        prev2 = prev;
        prev = c;
    }
    obj->vertex_cnt = cnt_vertex;
    obj->facet_cnt = cnt_facet;
    obj->matrix3d.rows = cnt_vertex;
    obj->matrix3d.cols = 3;
    if (cnt_vertex < 3)
        res = 0;
    return res;
}

void fill_matrix(data_t *obj, FILE *one) {
    int c = 0;
    int prev = '\n';
    int prev2 = 0;
    char *tmp2 = NULL;
    int index_rows = 1;
    int index_pol = 1;
    unsigned tmp_cnt = 0;
    size_t len = 0;
    obj->matrix3d.matrix = malloc((obj->vertex_cnt + 1) * sizeof(double*));
    for (unsigned i = 0; i < obj->vertex_cnt + 1; i++)
        obj->matrix3d.matrix[i] = malloc(3 * sizeof(double));
    obj->polygons = malloc((obj->facet_cnt + 1) * sizeof(facets_t));
    while ((c = fgetc(one)) != EOF) {
        if (prev == 'v' && prev2 == '\n' && c == ' ') {
            skip_spaces(one);
            fscanf(one, "%lf", &(obj->matrix3d.matrix[index_rows][0]));
            skip_spaces(one);
            fscanf(one, "%lf", &(obj->matrix3d.matrix[index_rows][1]));
            skip_spaces(one);
            fscanf(one, "%lf", &(obj->matrix3d.matrix[index_rows][2]));
            index_rows++;
        }
        if (prev == 'f' && prev2 == '\n' && c == ' ') {
            getline(&tmp2, &len, one);
            obj->polygons[index_pol].numbers_of_vertexes_in_facets = cnt_verts_in_facet(tmp2);
            obj->polygons[index_pol].vertexes =\
             malloc(obj->polygons[index_pol].numbers_of_vertexes_in_facets * sizeof(int));
            fill_facet_array(obj, tmp2, index_pol);
            index_pol++;
            c = fgetc(one);
            prev2 = '\n';
            prev = c;
        } else {
            prev2 = prev;
            prev = c;
        }
    }
    free(tmp2);
    fclose(one);
    from_matr_to_array(obj);
    tmp_cnt = obj->facet_cnt;
    polyg_array(obj);
    for (unsigned i = 0; i < obj->vertex_cnt + 1; i++)
        free(obj->matrix3d.matrix[i]);
    free(obj->matrix3d.matrix);
    for (unsigned i = 1; i < tmp_cnt + 1; i++)
        free(obj->polygons[i].vertexes);
    free(obj->polygons);
}

void skip_spaces(FILE* one) {
    int c = ' ';
    while (c == ' ')
        c = fgetc(one);
    ungetc(c, one);
}

int cnt_verts_in_facet(char *src) {
    int flag = 1;
    int cnt = 0;
    for (int i = 0; src[i] && src[i] != '\n' && src[i] != '\r'; i++) {
        if (src[i] == ' ') {
            flag = 1;
            continue;
        }
        if (flag) {
            cnt++;
            flag = 0;
        }
    }
    return cnt;
}

void fill_facet_array(data_t *obj, char *src, int index_pol) {
    int index_vert = 0;
    for (int i = 0; src[i] && src[i] != '\n' && src[i] != '\r'; i++) {
        if (src[i] == ' ') {
            continue;
        } else {
            sscanf(src + i, "%u", &(obj->polygons[index_pol].vertexes[index_vert]));
            index_vert++;
            while (src[i] != ' ' && src[i] != '\n' && src[i] != 0 && src[i] != '\r')
                i++;
        }
    }
}

void from_matr_to_array(data_t *obj) {
    int s = 0;
    obj->dst = malloc(sizeof(double) * obj->matrix3d.rows * 3);
    for (unsigned i = 1; i < obj->matrix3d.rows + 1; i++) {
        for (int n = 0; n < 3; n++) {
            obj->dst[s] = obj->matrix3d.matrix[i][n];
            s++;
        }
    }
}

void polyg_array(data_t *obj) {
    int s = 0;
    obj->polyg = malloc(6 * obj->facet_cnt * sizeof(unsigned));
    for (unsigned i = 1; i < obj->facet_cnt + 1; i++) {
        obj->polyg[s] = obj->polygons[i].vertexes[0]- 1;
        s++;
        obj->polyg[s] = obj->polygons[i].vertexes[1] - 1;
        s++;
        obj->polyg[s] = obj->polygons[i].vertexes[1] - 1;
        s++;
        obj->polyg[s] = obj->polygons[i].vertexes[2] - 1;
        s++;
        obj->polyg[s] = obj->polygons[i].vertexes[2] - 1;
        s++;
        obj->polyg[s] = obj->polygons[i].vertexes[0] - 1;
        s++;
    }
    obj->facet_cnt = s;
}

void move_x(data_t *obj, double offset) {
    for (unsigned i = 0; i < obj->vertex_cnt * 3; i++) {
        if (i % 3 == 0)
            obj->dst[i] += offset;
    }
}

void move_y(data_t *obj, double offset) {
    for (unsigned i = 0; i < obj->vertex_cnt * 3; i++) {
        if (i % 3 == 1)
            obj->dst[i] += offset;
    }
}

void move_z(data_t *obj, double offset) {
    for (unsigned i = 0; i < obj->vertex_cnt * 3; i++) {
        if (i % 3 == 2)
            obj->dst[i] += offset;
    }
}

void rotation_by_ox(data_t *obj, double angle) {
    double temp_y = 0;
    double temp_z = 0;
    for (unsigned i = 0; i < obj->vertex_cnt * 3; i++) {
        if (i % 3 == 1) {
            temp_y = obj->dst[i];
            temp_z = obj->dst[i+1];
            obj->dst[i] = cos(angle) * temp_y - sin(angle) * temp_z;
        }
        if (i % 3 == 2)
            obj->dst[i] = sin(angle) * temp_y + cos(angle) * temp_z;
    }
}

void zoom(data_t *obj, double k) {
    for (unsigned i = 0; i < obj->vertex_cnt * 3; i++) {
        obj->dst[i] *= k;
    }
}

void rotation_by_oy(data_t *obj, double angle) {
    double temp_x = 0;
    double temp_z = 0;
    for (unsigned i = 0; i < obj->vertex_cnt * 3; i++) {
        if (i % 3 == 0) {
            temp_x = obj->dst[i];
            temp_z = obj->dst[i+2];
            obj->dst[i] = cos(angle) * temp_x + sin(angle) * temp_z;
        }
        if (i % 3 == 2)
            obj->dst[i] = sin(angle) * -temp_x + cos(angle) * temp_z;
    }
}
void rotation_by_oz(data_t *obj, double angle) {
    double temp_x = 0;
    double temp_y = 0;
    for (unsigned i = 0; i < obj->vertex_cnt * 3; i++) {
        if (i % 3 == 0) {
            temp_x = obj->dst[i];
            temp_y = obj->dst[i+1];
            obj->dst[i] = cos(angle) * temp_x - sin(angle) * temp_y;
        }
        if (i % 3 == 1)
            obj->dst[i] = sin(angle) * temp_x + cos(angle) * temp_y;
    }
}
