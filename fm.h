#ifndef FM_H
#define FM_H

#include "bstset.h"
#include "provided.h"

#include <fstream> // TODO REMOVE ERROR
#include <sstream>

#include <unordered_map>
#include <vector>

using namespace std;


bool operator>(const FlightSegment& a, const FlightSegment& b) {
    return a.departure_time > b.departure_time;
}

bool operator==(const FlightSegment& a, const FlightSegment& b) {
    return a.departure_time == b.departure_time;
}

bool operator<(const FlightSegment& a, const FlightSegment& b) {
    return a.departure_time < b.departure_time;
} // TODO: YOU ONLY NEED ONE OF THESE OPERATOR DEFINITIONS


class FlightManager : public FlightManagerBase{
    public:
        FlightManager(){

        }
        ~FlightManager(){

        }

        bool load_flight_data(std::string filename) override{
            ifstream file(filename);
        
            if (!file){
                return false;
            }

            string line;
            while (getline(file, line)) {
                istringstream ss(line);
                string airline, src, dest, flight_num_str, dep_str, arr_str, dur_str;
                
                if (!getline(ss, airline, ',') ||
                    !getline(ss, flight_num_str, ',') ||
                    !getline(ss, src, ',') ||
                    !getline(ss, dest, ',') ||
                    !getline(ss, dep_str, ',') ||
                    !getline(ss, arr_str, ',') ||
                    !getline(ss, dur_str, ',')) {
                    continue;
                } //if not valid line of text

                //cerr << "Airline: " << airline << ", Flight Number: " << flight_num_str <<endl;
                //with this line ^ we confirmed that all flights are being read


                FlightSegment flight(airline, stoi(flight_num_str), src, dest, stoi(dep_str), stoi(dur_str));
                //cerr << flight.airline << " " << flight_num_str << " taking off from " << src << " added to hash map" << endl;
                flights_by_airport[src].insert(flight); //adding the flight to the BST for that airport
                //cerr << "Now there are " << flights_by_airport[src].size() <<" in " ; //doesnt work

                
                // auto it = flights_by_airport.find(src); //find bucket in hash map for src airport TODO REMOVE CERR
                // auto flight_set = it->second; // TODO REMOVE CERR
                // cerr << "Flights from " << src << ":" << endl; //CERR TODO REMOVE
                // flight_set.print_tree();  // Print the entire BST // CERR TODO REMOVE

                //cerr << "Number of airports? " << flights_by_airport.size()<<endl;
                //TODO check that hash table has stuff

            } //end while loop

            return true;
        }

        vector<FlightSegment> find_flights(string source_airport, int start_time, int end_time) const override{



            vector<FlightSegment> flights;

            
            
            
            cerr << "Source airport: " << source_airport << endl; // TODO REMOVE

            auto it = flights_by_airport.find(source_airport); //find bucket in hash map for src airport
            if (it == flights_by_airport.end()) { // if source_airport not found
                return flights;
            }

            auto& flight_set = it->second; //puts BST of flights from an airport into flight_set 
            auto iter = flight_set.find_first_not_smaller({ "", 0, source_airport, "", start_time, start_time}); //starting from all flights after start_time

            //flight_set.print_tree();  // Print the entire BST // CERR TODO REMOVE. Don't remove two lines above to make flight set and stuff
            

            const FlightSegment* flight;
            while ((flight = iter.get_and_advance()) != nullptr) {
                if (flight->departure_time >= end_time){
                    //cerr << "Earliest start time: " << start_time <<endl;
                    //cerr << "End time boundary: " << end_time << endl;
                    //cerr << "Depart time: "<<flight->departure_time <<endl;
                    
                    break;
                }
                //cerr << "Depart time of this flight: " << flight->departure_time <<endl;
                flights.push_back(*flight);
                //cerr << flights.size()<<endl; // TODO REMOVE. Problem is that we only add 1 flight to here
                //cerr << flight->airline << " " << flight->flight_no << " taking off from (fm.h)" << flight->source_airport << endl; //useful debugging statement for tp.h
                // if((flight=iter.get_and_advance()) == nullptr){
                //     cerr << "next thing is a nullptr" <<endl;
                // } //REMOVE

                //problem is either that my get_and_advance is going to the wrong thing or that the BST is only one node big (improper insertions)
                // taktes this before dying "Advanced Air,711,HHR,MCE,1736361000,1736365680,4680"
            }

            return flights;
        }

    private:
        unordered_map<string, BSTSet<FlightSegment>> flights_by_airport;

};

/*
Flight Segment:

■ Airline Name – A string indicating the airline offering the flight (e.g.,
"Korean Air").
■ Flight Number – An integer representing the flight number assigned by
the airline.
■ Source Airport – A string containing the three-letter airport code where
the flight departs.
■ Destination Airport – A string containing the three-letter airport code
where the flight arrives.
■ Departure Time – An integer (UNIX timestamp in seconds) indicating
when the flight is scheduled to depart.
■ Duration (Seconds) – An
*/

// class FlightManagerBase
// {
//   public:
//     FlightManagerBase() {}
//     virtual ~FlightManagerBase() {}

//     virtual bool load_flight_data(std::string filename) = 0;
//     virtual std::vector<FlightSegment> find_flights(std::string source_airport, int start_time, int end_time) const = 0;
// };

#endif
