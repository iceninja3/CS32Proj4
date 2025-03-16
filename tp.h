#ifndef TP_H
#define TP_H

#include "provided.h"
#include "fm.h"
#include <queue>
#include <set>
#include <unordered_map>

using namespace std;


class TravelPlanner : public TravelPlannerBase {
    private:
        set<string> preferred_airlines; 

public:
    TravelPlanner(const FlightManagerBase& flight_manager, const AirportDB& airport_db)
        : TravelPlannerBase(flight_manager, airport_db) {}
    ~TravelPlanner() {}

    void add_preferred_airline(string airline) override {
        //cerr << "Preferred airline: " << airline <<endl; //checking if airlines are added to the vector for them
        preferred_airlines.insert(airline);
    }

    bool plan_travel(std::string source_airport, std::string destination_airport, int start_time, Itinerary& itinerary) const override {
        struct State {
            std::vector<FlightSegment> flights;
            int arrival_time;
        };

        std::queue<State> bfs_queue;
        bfs_queue.push({{}, start_time});

        std::unordered_map<std::string, int> best_arrival;
        best_arrival[source_airport] = start_time;

        while (!bfs_queue.empty()) {
            State current = bfs_queue.front();
            bfs_queue.pop();

            std::string last_airport = current.flights.empty() ? source_airport : current.flights.back().destination_airport;
            int min_depart_time = current.arrival_time + (current.flights.empty() ? 0 : get_min_connection_time());
            int max_depart_time = current.arrival_time + get_max_layover();

            if (current.arrival_time - start_time > get_max_duration())
                continue;

            if (last_airport == destination_airport) {
                itinerary.source_airport = source_airport;
                itinerary.destination_airport = destination_airport;
                itinerary.flights = current.flights;
                itinerary.total_duration = current.arrival_time - start_time;
                return true;
            }

            for (const FlightSegment& flight : get_flight_manager().find_flights(last_airport, min_depart_time, max_depart_time)) {
                int new_arrival_time = flight.departure_time + flight.duration_sec;
                if (best_arrival.find(flight.destination_airport) == best_arrival.end() || new_arrival_time < best_arrival[flight.destination_airport]) {
                    best_arrival[flight.destination_airport] = new_arrival_time;
                    State new_state = current;
                    new_state.flights.push_back(flight);
                    new_state.arrival_time = new_arrival_time;
                    bfs_queue.push(new_state);
                    itinerary.flights.push_back(flight); // Ensure flights are added to the itinerary
                }
            }
        }

        return true;
        return false;

    }//end plan_travel function

};


#endif // TP_H
