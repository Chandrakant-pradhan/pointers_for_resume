"""
Lab week 1: Question 1: Linear programs

Implement solvers to solve linear programs of the form:

max c^{T}x
subject to:
Ax <= b
x >= 0

(a) Firstly, implement simplex method covered in class from scratch to solve the LP

simplex reference:
https://www.youtube.com/watch?v=t0NkCDigq88
"""
import numpy
import pulp
import pandas as pd
import argparse


def parse_commandline_args():
    """Parse command line arguments"""
    parser = argparse.ArgumentParser()
    parser.add_argument('--testDirectory', type=str, required=True, help='Directory of the test case files')
    arguments = parser.parse_args()
    return arguments


def simplex_solver(A_matrix: numpy.array, c: numpy.array, b: numpy.array) -> list:
    """
    Implement LP solver using simplex method.

    :param A_matrix: Matrix A from the standard form of LP
    :param c: Vector c from the standard form of LP
    :param b: Vector b from the standard form of LP
    :return: list of pivot values simplex method encountered in the same order
    """
    pivot_value_list = []
    ################################################################
    # %% Student Code Start
    # Implement here
    op_matrix = [[0.0 for i in range(len(c) + len(A_matrix) + 1)] for j in range(len(A_matrix)+1)]
    for i in range(len(A_matrix)):
        op_matrix[i][0:len(A_matrix)] = A_matrix[i]
        op_matrix[i][-1] = b[i]
        op_matrix[i][len(c)+i] = 1.0

    for i in range(len(c)):
        op_matrix[-1][i] = -c[i]

    while(True):
        is_over = True
        for i in range(len(c)):
            if(op_matrix[len(A_matrix)][i] != 0):
                is_over = False
                break
        if(is_over):
            break

        index_of_min = numpy.argmin(op_matrix[len(A_matrix)][0:len(c)])
        for j in range(len(A_matrix)):
            


        



    
    # %% Student Code End
    ################################################################

    # Transfer your pivot values to pivot_value_list variable and return
    return pivot_value_list


if __name__ == "__main__":
    # get command line args
    args = parse_commandline_args()
    if args.testDirectory is None:
        raise ValueError("No file provided")
    # Read the inputs A, b, c and run solvers
    # There are 2 test cases provided to test your code, provide appropriate command line args to test different cases.
    matrix_A = pd.read_csv("{}/A.csv".format(args.testDirectory), header=None, dtype=float).to_numpy()
    vector_c = pd.read_csv("{}/c.csv".format(args.testDirectory), header=None, dtype=float)[0].to_numpy()
    vector_b = pd.read_csv("{}/b.csv".format(args.testDirectory), header=None, dtype=float)[0].to_numpy()

    simplex_pivot_values = simplex_solver(matrix_A, vector_c, vector_b)
    for val in simplex_pivot_values:
        print(val)
