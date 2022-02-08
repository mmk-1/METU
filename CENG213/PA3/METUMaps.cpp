#include "METUMaps.h"
#include "GraphExceptions.h"

#include <iostream>

void METUMaps::PrintNotInJourney() const
{
    std::cout << "Device is not in a journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeDestination() const
{
    std::cout << "Cannot change Destination during journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeStartingLoc() const
{
    std::cout << "Cannot change Starting Location during journey!" << std::endl;
}

void METUMaps::PrintAlreadyInJourney() const
{
    std::cout << "Device is already in a journey!" << std::endl;
}

void METUMaps::PrintJourneyIsAlreadFinished() const
{
    std::cout << "Journey is already finished!" << std::endl;
}

void METUMaps::PrintLocationNotFound() const
{
    std::cout << "One (or both) of the locations are not found in the maps!" << std::endl;
}

void METUMaps::PrintJourneyCompleted() const
{
    std::cout << "Journey Completed!" << std::endl;
}

void METUMaps::PrintCachedLocationFound(const std::string& location0,
                                        const std::string& location1) const
{
    std::cout << "Route between \""
              << location0 << "\" and \""
              << location1 << "\" is in cache, using that..."
              << std::endl;
}

void METUMaps::PrintCalculatingRoutes(const std::string& location0,
                                      const std::string& location1) const
{
    std::cout << "Calculating Route(s) between \""
              << location0 << "\" and \""
              << location1 << "\"..."
              << std::endl;
}

std::string METUMaps::GenerateKey(const std::string& location0,
                                  const std::string& location1)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    return location0 + "/" + location1;
}

METUMaps::METUMaps(int potentialPathCount,
                   const std::string& mapFilePath)
{
    // TODO
    Graph newMap(mapFilePath);
    this->map = newMap;
    this->potentialPathCount = potentialPathCount;
    this->inJourney = false;
    int locations = this->map.TotalVertexCount();
    KeyedHashTable newHashTable(potentialPathCount*locations);
    this->cachedPaths = newHashTable;
}

void METUMaps::SetDestination(const std::string& name)
{
    // TODO
    if(this->inJourney)
    {
        PrintUnableToChangeDestination();
        return;
    }
    this->destination = name;
}

void METUMaps::SetStartingLocation(const std::string& name)
{
    // TODO
    if(this->inJourney)
    {
        PrintUnableToChangeStartingLoc();
        return;
    }
    this->startingLoc = name;
}

void METUMaps::StartJourney()
{
    // TODO
    PrintCalculatingRoutes(startingLoc, destination);
    if(!ContainsLocation(startingLoc) || !ContainsLocation(destination))
    {
        PrintLocationNotFound();
        return;
    }
    if(inJourney)
    {
        PrintAlreadyInJourney();
        return;
    }
    std::vector<std::vector<int> > paths;
    this->map.MultipleShortPaths(paths, startingLoc, destination, potentialPathCount);
    Cache(paths);
    currentLoc = startingLoc;
    currentRoute = paths[0];
    inJourney = true;
}

void METUMaps::EndJourney()
{
    // TODO
    if(!inJourney)
    {
        PrintJourneyIsAlreadFinished();
        return;
    }
    cachedPaths.ClearTable();
    inJourney = false;
    destination.clear();
    startingLoc.clear();
    currentLoc.clear();
}

void METUMaps::UpdateLocation(const std::string& name)
{
    // TODO
    if(!inJourney)
    {
        PrintNotInJourney();
        return;
    }
    if(!ContainsLocation(const_cast <std::string&> (name)))
    {
        PrintLocationNotFound();
        return;
    }
    if(name == destination)
    {
        PrintJourneyCompleted();
        return;
    }
    std::string lookForKey = GenerateKey(name, destination);
    std::vector<int> newRoute;
    bool newRouteExists = cachedPaths.Find(newRoute, lookForKey);
    if(newRouteExists)
    {
        PrintCachedLocationFound(name, destination);
        currentRoute = newRoute;
        currentLoc = name;
        // return;
    }
    else{
        newRoute.clear();
        PrintCalculatingRoutes(name, destination);
        map.ShortestPath(newRoute, name, destination);
        std::vector<std::vector<int> > paths;
        paths.push_back(newRoute);
        Cache(paths);
        currentRoute = newRoute;
        currentLoc = name;
    }
}

void METUMaps::Display()
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    if(!inJourney)
    {
        // We are not in journey, this function
        // shouldn't be called
        PrintNotInJourney();
        return;
    }

    int timeLeft = map.TotalWeightInBetween(currentRoute);

    // Print last known location
    std::cout << "Journey         : " << startingLoc << "->"
              << destination << "\n";
    std::cout << "Current Location: " << currentLoc << "\n";
    std::cout << "Time Left       : " << timeLeft << " minutes\n";
    std::cout << "Current Route   : ";
    map.PrintPath(currentRoute, true);

    std::cout.flush();
}

// Custom functions

void METUMaps::Cache(std::vector<std::vector<int> > &paths)
{
    // KeyedHashTable newCachedHash(map.TotalVertexCount()*potentialPathCount);
    for(int i = 0;i<paths.size();i++)
    {
        std::vector<int> currPath = paths[i];
        while (currPath.size()>1)
        {
            std::string currStart = map.VertexName(currPath.front());
            std::string currDest = map.VertexName(currPath.back());
            std::string key = GenerateKey(currStart, currDest);
            cachedPaths.Insert(key, currPath);
            currPath.erase(currPath.begin());
        }
    }
}


bool METUMaps::ContainsLocation(std::string &name) const 
        {
            int size = map.TotalVertexCount();
            for(int i = 0; i< size ; i++)
            {
                if(map.VertexName(i) == name)
                {
                    return true;
                }
            }
            return false;
}
