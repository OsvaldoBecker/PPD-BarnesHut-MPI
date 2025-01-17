/*
 * File: barnes_hut.h: header file for barnes_hut.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi/mpi.h>

/*
 * Struct that represents a state of states vector.
 */
struct state_t
{
    double x, y, u, v, force_x, force_y, mass;
};

/*
 * Struct that represents a node of the Barnes Hut quad tree.
 */
struct node_t
{
    int particle;
    int has_particle;
    int has_children;
    double min_x, max_x, min_y, max_y, total_mass, c_x, c_y;
    struct node_t *children;
};

// Calculates the positions of a time step
void time_step(void);

// Functions for the force calculations
void calculate_states(int point, int end);
void update_forces(int particle, struct node_t *node);
void calculate_force(int particle, struct node_t *node, double r);

// If a particle moves beyond any of the boundaries then bounce it back
void bounce(double *x, double *y, double *u, double *v);

// Functions for handling the placement of particles in the tree
void put_particle_in_tree(int new_particle, struct node_t *node);
void place_particle(int particle, struct node_t *node);
void set_node(struct node_t *node);
void free_node(struct node_t *node);

// Functions for calculating the mass and centre of mass of the tree
double calculate_mass(struct node_t *node);
double calculate_center_of_mass_x(struct node_t *node);
double calculate_center_of_mass_y(struct node_t *node);

// Functions to read file and prints statistics
int read_case(char *filename);
void print_statistics(float vu, float vv, float cx, float cy);