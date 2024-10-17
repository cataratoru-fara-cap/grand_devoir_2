#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <limits>
#include <queue>

using namespace std;

 vector<vector<int>> readCSVToGraph(const string& filename) {
    ifstream file(filename);
    vector< vector<int>> graph;
    string line, value;

    while (getline(file, line)) {
        vector<int> row;
        stringstream ss(line);
        while (getline(ss, value, ',')) {
            row.push_back( stoi(value));
        }
        graph.push_back(row);
    }

    return graph;
}

void writeGraphToCSV(const vector<vector<int>>& graph, const  string& filename) {
    ofstream file(filename);

    for (const auto &row : graph) {
        for (int i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i != row.size() - 1) {
                file << ',';
            }
        }
        file << '\n';
    }
}

vector<vector<int>> generateAdjacencyMatrix(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    int totalNodes = n * m + 2; // Adding 2 for the start and sink nodes
    vector<vector<int>> adjacencyMatrix(totalNodes, vector<int>(totalNodes, 0));

    // Connect start and sink nodes to all other nodes
    for (int i = 1; i <= n * m; i++) { // n*m = 36
        adjacencyMatrix[0][i] = 1; // Start to others
        adjacencyMatrix[i][totalNodes - 1] = 1; // Others to sink
    }

    // Connect each node to its neighbors
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            int nodeIndex = i * n + j  + 1; // +1 to account for the start node
            int x = nodeIndex;              //mindbending indexing...
            int y = nodeIndex;
            
            if (i > 0) adjacencyMatrix[x][y - n] = 1; // ! Up n = 6 (we shift like this because of node the node above will have number cur - n here n is the length of the square matrix)
            if (i < n - 1) adjacencyMatrix[x][y + m] = 1; // Down m = 6
            if (j > 0) adjacencyMatrix[x - 1][y] = 1; // Left
            if (j < m - 1) adjacencyMatrix[x + 1][y] = 1; // Right
        }
    }

    return adjacencyMatrix;
}

vector<vector<int>> generateResidualMatrix(vector<vector<int>> residualMatrix,const vector<vector<int>>& brightness){
    int n = brightness.size();
    int m = brightness[0].size();
    int totalNodes = n * m + 2;
    
    for (int i = 1; i <= n * m; i++) { // n*m = 36
        residualMatrix[0][i] = 0; // Start to others
        residualMatrix[i][totalNodes - 1] = 0; // Others to sink
        
        residualMatrix[i][0] = 255; // Start to others
        residualMatrix[totalNodes - 1][i] = 255;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            int nodeIndex = i * n + j  + 1; // +1 to account for the start node
            int x = nodeIndex;              //mindbending indexing...
            int y = nodeIndex;


            if ((i > 0) &&  abs(brightness[i][j] - brightness[i-1][j]) > 10 ) //if result is opposite of example, switch from > to <
                residualMatrix[x][y - n] = 255 - abs(brightness[i][j] - brightness[i-1][j]) ; // Up 
            else if ( y-n > 0 ) 
                residualMatrix[x][y - n] = 0;           

            if ((i < n - 1) && abs(brightness[i][j] - brightness[i+1][j]) > 10 )
                residualMatrix[x][y + m] = 255 - abs(brightness[i][j] - brightness[i+1][j]) ; // Down m = 6
            else if ( x < (m*n + 1) ) 
                residualMatrix[x][y + m] = 0;           

            if ((j > 0)  &&    abs(brightness[i][j] - brightness[i][j-1]) > 10 )
                residualMatrix[x - 1][y] = 255 - abs(brightness[i][j] - brightness[i][j-1]) ; // Left
            else if ( y > 0)
                residualMatrix[x - 1][y] = 0;           

            if ((j < m - 1) && abs(brightness[i][j] - brightness[i][j+1]) > 10 )
                residualMatrix[x + 1][y] = 255 - abs(brightness[i][j] - brightness[i][j+1]) ; // Right
            else if ( (x + 1) < (m*n + 1) )
                residualMatrix[x + 1][y] = 0;        
        } // else if's are necessary to protect against chainging of the start and sink
    }

    return residualMatrix;
}

// Function to perform BFS on the residual graph and
// return true if there is a path from source to sink


int main(int argc, char const *argv[])
{
    // Read the input matrix from input.csv
    vector<vector<int>> brightnessMatrix = readCSVToGraph("input.csv");
    // Generate the adjacency matrix
    vector<vector<int>> adjacencyMatrix = generateAdjacencyMatrix(brightnessMatrix);
    // Generate the residual matrix
    vector<vector<int>> residualMatrix = generateResidualMatrix(adjacencyMatrix, brightnessMatrix);


    // Write the adjacency matrix to output.csv
    writeGraphToCSV(adjacencyMatrix, "adjacency.csv");
    writeGraphToCSV(residualMatrix, "residual.csv");


    return 0;
}
