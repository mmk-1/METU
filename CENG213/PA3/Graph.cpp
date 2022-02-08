#include "Graph.h"
#include "GraphExceptions.h"

#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>

// Literally do nothing here
// default constructors of the std::vector is enough
Graph::Graph()
{}

Graph::Graph(const std::string& filePath)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    // Tokens
    std::string tokens[3];

    std::ifstream mapFile(filePath.c_str());
    // Read line by line
    std::string line;
    while (std::getline(mapFile, line))
    {
        // Empty Line Skip
        if(line.empty()) continue;
        // Comment Skip
        if(line[0] == '#') continue;

        // Tokenize the line
        int i = 0;
        std::istringstream stream(line);
        while(stream >> tokens[i]) i++;

        // Single token (Meaning it is a vertex)
        if(i == 1)
        {
            InsertVertex(tokens[0]);
        }
        // Exactly three tokens (Meaning it is an edge)
        else if(i == 3)
        {
            int weight = std::atoi(tokens[0].c_str());
            if(!ConnectVertices(tokens[1], tokens[2], weight))
            {
                std::cerr << "Duplicate edge on "
                          << tokens[0] << "-"
                          << tokens[1] << std::endl;
            }
        }
        else std::cerr << "Token Size Mismatch" << std::endl;
    }
}

void Graph::InsertVertex(const std::string& vertexName)
{
    // TODO
    for (int i = 0; i < vertexList.size(); i++)
    {
        if (vertexList[i].name == vertexName)
        {
            throw DuplicateVertexNameException();
        }
    }
    GraphVertex newVertex;
    newVertex.name = vertexName;
    newVertex.edgeCount = 0;
    this->vertexList.push_back(newVertex);
}

bool Graph::ConnectVertices(const std::string& fromVertexName,
                            const std::string& toVertexName,
                            int weight)
{
    // TODO
    if (fromVertexName == toVertexName)
    {
        return false;
    }
    bool fromExists = false, toExists = false;
    int id0, id1;
    for (int i = 0; i < vertexList.size(); i++)
    {
        if (vertexList[i].name == fromVertexName)
        {
            fromExists = true;
            id0 = i;
        }
        if (vertexList[i].name == toVertexName)
        {
            toExists = true;
            id1 = i;
        }
    }
    if (!fromExists || !toExists)
    {
        throw VertexNotFoundException();
    }
    if (vertexList[id0].edgeCount >= MAX_EDGE_PER_VERTEX || vertexList[id1].edgeCount >= MAX_EDGE_PER_VERTEX)
    {
        throw TooManyEdgeOnVertexExecption();
        // std::cout << "HELLO" << '\n';
    }
    // Check if edge exists between the vertices
    for (int j = 0; j < edgeList.size(); j++)
    {
        if ((edgeList[j].vertexId0 == id0 && edgeList[j].vertexId1 == id1) ||
            (edgeList[j].vertexId0 == id1 && edgeList[j].vertexId1 == id0))
        {
            return false;
        }
    }
    int edge0cnt = vertexList[id0].edgeCount, edge1cnt = vertexList[id1].edgeCount;
    GraphEdge newEdge;
    newEdge.masked = false;
    newEdge.vertexId0 = id0;
    newEdge.vertexId1 = id1;
    newEdge.weight = weight;
    edgeList.push_back(newEdge);
    int newEdgeId = edgeList.size() - 1;
    vertexList[id0].edgeIds[edge0cnt] = newEdgeId;
    vertexList[id1].edgeIds[edge1cnt] = newEdgeId;
    vertexList[id0].edgeCount++;
    vertexList[id1].edgeCount++;
    return true;
}

bool Graph::ShortestPath(std::vector<int>& orderedVertexIdList,
                         const std::string& from,
                         const std::string& to) const
{
    // TODO
    // std::cout << "myPATH: " << std::endl;
    // PrintPath(orderedVertexIdList, true);
    if (!ContainsVertex(from) || !ContainsVertex(to))
    {
        throw VertexNotFoundException();
    }
    if(from == to){
        // getVertexId(from);
        orderedVertexIdList.push_back(getVertexId(from));
        return true;
    }
    // min heap
    // std::priority_queue<DistanceVertexIdPair, std::vector<DistanceVertexIdPair>, std::greater<DistanceVertexIdPair> > pq;
    std::priority_queue<DistanceVertexIdPair> pq;
    // known vertices
    std::vector<bool> known(vertexList.size(), false);
    //parents
    std::vector<int> parent(vertexList.size(), -2);
    int fromVertexId = getVertexId(from);
    // std::cout << fromVertexId << '\n';
    int toVertexId = getVertexId(to);
    // std::cout << toVertexId << '\n';
    std::vector<DistanceVertexIdPair> verticesVector;
    // std::cout << "one" << '\n';
    for (int i = 0; i < vertexList.size(); i++)
    {   
        if (i == fromVertexId)
        {
            pq.push(DistanceVertexIdPair(i, 0));
            verticesVector.push_back(DistanceVertexIdPair(i, 0));
        }
        else
        {
            pq.push(DistanceVertexIdPair(i, LARGE_NUMBER));
            verticesVector.push_back(DistanceVertexIdPair(i, LARGE_NUMBER));
        }
    }
    // std::cout << " SIZE " << verticesVector.size() << '\n';
    // std::cout << "two" << '\n';
    // While not empty
    while (!pq.empty())
    {
        // std::cout << "One" << '\n';
        DistanceVertexIdPair V = pq.top();
        pq.pop();
        // check if it is the destination
        if (V.vId == toVertexId)
        {
            break;
        }
        if (known[V.vId])
        {
            continue;
        }
        // make it known
        known[V.vId] = true;
        // For each edge (adjecent vertex W) of V
        for (int k = 0; k < vertexList[V.vId].edgeCount; k++)
        {
            int currEdgeId = vertexList[V.vId].edgeIds[k];
            if(edgeList[currEdgeId].masked){
                continue;
            }
            int tempDist = V.currentWeight + edgeList[currEdgeId].weight;
            int W = edgeList[currEdgeId].vertexId0 == V.vId ? edgeList[currEdgeId].vertexId1 : edgeList[currEdgeId].vertexId0;
            if (tempDist < verticesVector[W].currentWeight && !known[W] && !edgeList[currEdgeId].masked)
            {
                // update W.currWeight
                verticesVector[W].currentWeight = tempDist;
                // update in heap :DAS:DADADADSADSLKDKSJADLKSAJDLAD
                // todo
                pq.push(DistanceVertexIdPair(W, tempDist));
                // assign parent
                parent[W] = V.vId;
            }
        }
    }
    parent[fromVertexId] = -1;
    int ind = toVertexId;
    while(ind != -1){
        if(ind == -2){
            orderedVertexIdList.clear();
            return false;
        }
        orderedVertexIdList.insert(orderedVertexIdList.begin(), ind);
        ind = parent[ind];
    }
    return true;
}

int Graph::MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,
                              const std::string& from,
                              const std::string& to,
                              int numberOfShortestPaths)
{
    // TODO
    if(!ContainsVertex(from) || !ContainsVertex(to)){
        throw VertexNotFoundException();
    }
    UnMaskAllEdges();
    std::vector<int> lastPath;
    bool gotShortestPath = ShortestPath(lastPath, from, to);
    if(lastPath.size() == 0) {
        return 0;
    }
    orderedVertexIdList.push_back(lastPath);
    for(int i = 1; i < numberOfShortestPaths; i++){
        // lastPath = orderedVertexIdList[i];
        
        // std::cout << "LAST" << '\n';
        // PrintPath(lastPath, true);
        
        maskHighestWeightedEdge(lastPath);
        
        std::vector<int> newPath;
        
        gotShortestPath = ShortestPath(newPath, from, to);
        
        // std::cout << "MY:  " << gotShortestPath << '\n';
        
        if(gotShortestPath == false){
            break;
        }
        
        // std::cout << "MY:  " << gotShortestPath << '\n';
        // PrintPath(newPath, true);
        
        orderedVertexIdList.push_back(newPath);
        lastPath = orderedVertexIdList.back();
    }
//   std::cout << "size: " <<  orderedVertexIdList.size() << '\n';
    UnMaskAllEdges();
    return orderedVertexIdList.size();
}

void Graph::MaskEdges(const std::vector<StringPair>& vertexNames)
{
    // TODO
    using namespace std;
    for (int i = 0; i < vertexNames.size(); i++)
    {
        string v0Name = vertexNames[i].s0;
        string v1Name = vertexNames[i].s1;
        if (!ContainsVertex(v0Name) || !ContainsVertex(v1Name))
        {
            throw VertexNotFoundException();
        }
        int v0Id = getVertexId(v0Name);
        int v1Id = getVertexId(v1Name);
        for (int j = 0; j < edgeList.size(); j++)
        {
            if ((edgeList[j].vertexId0 == v0Id && edgeList[j].vertexId1 == v1Id) ||
                (edgeList[j].vertexId0 == v1Id && edgeList[j].vertexId1 == v0Id))
            {
                edgeList[j].masked = true;
            }
        }
    }
}

void Graph::UnMaskEdges(const std::vector<StringPair>& vertexNames)
{
    // TODO
    using namespace std;
    for (int i = 0; i < vertexNames.size(); i++)
    {
        string v0Name = vertexNames[i].s0;
        string v1Name = vertexNames[i].s1;
        if (!ContainsVertex(v0Name) || !ContainsVertex(v1Name))
        {
            throw VertexNotFoundException();
        }
        int v0Id = getVertexId(v0Name);
        int v1Id = getVertexId(v1Name);
        for (int j = 0; j < edgeList.size(); j++)
        {
            if ((edgeList[j].vertexId0 == v0Id && edgeList[j].vertexId1 == v1Id) ||
                (edgeList[j].vertexId0 == v1Id && edgeList[j].vertexId1 == v0Id))
            {
                edgeList[j].masked = false;
            }
        }
    }
}

void Graph::UnMaskAllEdges()
{
    // TODO
    for (int i = 0; i < edgeList.size(); i++)
    {
        edgeList[i].masked = false;
    }
}

void Graph::MaskVertexEdges(const std::string& name)
{
    // TODO
    if (!ContainsVertex(name))
    {
        throw VertexNotFoundException();
    }
    int myVertexId = getVertexId(name);
    for (int i = 0; i < vertexList[myVertexId].edgeCount; i++)
    {
        int myEdgeId = vertexList[myVertexId].edgeIds[i];
        edgeList[myEdgeId].masked = true;
    }
}

void Graph::UnMaskVertexEdges(const std::string& name)
{
    // TODO
    if (!ContainsVertex(name))
    {
        throw VertexNotFoundException();
    }
    int myVertexId = getVertexId(name);
    for (int i = 0; i < vertexList[myVertexId].edgeCount; i++)
    {
        int myEdgeId = vertexList[myVertexId].edgeIds[i];
        edgeList[myEdgeId].masked = false;
    }
}

void Graph::ModifyEdge(const std::string& vName0,
                       const std::string& vName1,
                       float newWeight)
{
    // TODO
    if (!ContainsVertex(vName0) || !ContainsVertex(vName1))
    {
        throw VertexNotFoundException();
    }
    int v0Id = getVertexId(vName0);
    int v1Id = getVertexId(vName1);
    for (int j = 0; j < edgeList.size(); j++)
    {
        if ((edgeList[j].vertexId0 == v0Id && edgeList[j].vertexId1 == v1Id) ||
            (edgeList[j].vertexId0 == v1Id && edgeList[j].vertexId1 == v0Id))
        {
            edgeList[j].weight = (int)newWeight;
        }
    }
}

void Graph::ModifyEdge(int vId0, int vId1,
                       float newWeight)
{
    // TODO
    // if (!ContainsVertex(vId0) || !ContainsVertex(vId1))
    // {
    //     return;
    // }
    for (int j = 0; j < edgeList.size(); j++)
    {
        if ((edgeList[j].vertexId0 == vId0 && edgeList[j].vertexId1 == vId1) ||
            (edgeList[j].vertexId0 == vId1 && edgeList[j].vertexId1 == vId0))
        {
            edgeList[j].weight = (int)newWeight;
        }
    }
}

void Graph::PrintAll() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    for(size_t i = 0; i < vertexList.size(); i++)
    {
        const GraphVertex& v = vertexList[i];
        std::cout << v.name << "\n";
        for(int j = 0; j < v.edgeCount; j++)
        {
            int edgeId = v.edgeIds[j];
            const GraphEdge& edge = edgeList[edgeId];
            // Skip printing this edge if it is masked
            if(edge.masked)
                continue;

            // List the all vertex names and weight
            std::cout << "-" << std::setfill('-')
                             << std::setw(2) << edge.weight
                             << "-> ";
            int neigVertexId = (static_cast<int>(i) == edge.vertexId0)
                                 ? edge.vertexId1
                                 : edge.vertexId0;
            std::cout << vertexList[neigVertexId].name << "\n";
        }
    }
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

void Graph::PrintPath(const std::vector<int>& orderedVertexIdList,
                      bool sameLine) const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this file !       //
    // ============================= //
    for(size_t i = 0; i < orderedVertexIdList.size(); i++)
    {
        int vertexId = orderedVertexIdList[i];
        if(vertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        const GraphVertex& vertex = vertexList[vertexId];
        std::cout << vertex.name;
        if(!sameLine) std::cout << "\n";
        // Only find and print the weight if next is available
        if(i == orderedVertexIdList.size() - 1) break;
        int nextVertexId = orderedVertexIdList[i + 1];
        if(nextVertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        // Find the edge between these two vertices
        int edgeId = INVALID_INDEX;
        if(vertexId     < static_cast<int>(vertexList.size()) &&
           nextVertexId < static_cast<int>(vertexList.size()))
        {
            // Check all of the edges of vertex
            // and try to find
            const GraphVertex& fromVert = vertexList[vertexId];
            for(int i = 0; i < fromVert.edgeCount; i++)
            {
                int eId = fromVert.edgeIds[i];
                // Since the graph is not directional
                // check the both ends
                if((edgeList[eId].vertexId0 == vertexId &&
                    edgeList[eId].vertexId1 == nextVertexId)
                ||
                   (edgeList[eId].vertexId0 == nextVertexId &&
                    edgeList[eId].vertexId1 == vertexId))
                {
                    edgeId = eId;
                    break;
                }
            }
        }
        if(edgeId != INVALID_INDEX)
        {
            const GraphEdge& edge = edgeList[edgeId];
            std::cout << "-" << std::setfill('-')
                      << std::setw(2)
                      << edge.weight << "->";
        }
        else
        {
            std::cout << "-##-> ";
        }
    }
    // Print endline on the last vertex if same line is set
    if(sameLine) std::cout << "\n";
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

int Graph::TotalVertexCount() const
{
    // TODO
    return vertexList.size();
}

int Graph::TotalEdgeCount() const
{
    // TODO
    return edgeList.size();
}

std::string Graph::VertexName(int vertexId) const
{
    // TODO
    for (int i = 0; i < vertexList.size(); i++)
    {
        if (i == vertexId)
            return vertexList[i].name;
    }
    return "";
}

int Graph::TotalWeightInBetween(std::vector<int>& orderedVertexIdList)
{
    // TODO
    bool noEdgesAtAll = true;
    int totalWeight = 0;
    for(int i = 0; i<orderedVertexIdList.size()-1;i++){
        if(!ContainsVertex(orderedVertexIdList[i]) || !ContainsVertex(orderedVertexIdList[i+1])){
            throw VertexNotFoundException();
        }
        int currEdgeId = findEdge(orderedVertexIdList[i], orderedVertexIdList[i+1]);
        if(currEdgeId == -1){
            continue;
        }
        totalWeight += edgeList[currEdgeId].weight;
        noEdgesAtAll = false;
    }
    if(noEdgesAtAll){
        return -1;
    }
    return totalWeight;
}

// Custom functions
bool Graph::ContainsVertex(std::string vertexName) const
{
    for (int i = 0; i < vertexList.size(); i++)
    {
        if (vertexList[i].name == vertexName)
        {
            return true;
        }
    }
    return false;
}

bool Graph::ContainsVertex(int vertexId) const
{
    for (int i = 0; i < vertexList.size(); i++)
    {
        if (i == vertexId)
        {
            return true;
        }
    }
    return false;
}

int Graph::getVertexId(std::string vertexName) const
{
    if (!ContainsVertex(vertexName))
    {
        return -1;
    }
    for (int i = 0; i < vertexList.size(); i++)
    {
        if (vertexList[i].name == vertexName)
        {
            return i;
        }
    }
    return -1;
}

int Graph::findEdge(int v0, int v1){
        for(int i=0;i<edgeList.size();i++){
            if((edgeList[i].vertexId0 == v0 && edgeList[i].vertexId1 == v1) ||
               (edgeList[i].vertexId0 == v1 && edgeList[i].vertexId1 == v0))
               {
                   return i;
               }
        }
        //return -1 if no edge;
        return -1;
}

void Graph::maskHighestWeightedEdge(std::vector<int> &lastPath){
        int maxWeight = -1;
        int maxEdgeId = -1;
        for(int i = 0;i<(lastPath.size()-1);i++){
                int currVertexId = lastPath[i];
                int nextVertexId = lastPath[i+1];
                int currEdgeId = findEdge(currVertexId, nextVertexId);
                if(edgeList[currEdgeId].weight > maxWeight){
                    maxWeight = edgeList[currEdgeId].weight;
                    maxEdgeId = currEdgeId;
                }
        }
        edgeList[maxEdgeId].masked = true;
}