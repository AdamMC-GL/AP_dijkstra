#include <stdio.h>
#include <iostream> 
#include <string>
#include <ctime>
#include <vector>
#include <math.h>
#include <limits>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

class Train{
public:
	string name_start;
	string name_end;
	int duration_min;
	
	int get_duration(){
		return duration_min;
	}

};

class Ride{
public:
	string name_start;
	string name_end;
	int kilometer;
	
	int get_kilometer(){
		return kilometer;
	}

};

class Flight{
public:
	string name_start;
	string name_end;
	int cost;
	
	int get_cost(){
		return cost;
	}

};

class Step{
public:
	string name;
	vector<Train> train_neighbours;
	vector<Ride> ride_neighbours;
	vector<Flight> flight_neighbours;
	
	void add_train_step(Train tr_arg){
		train_neighbours.push_back(tr_arg);
	}
	void add_ride_step(Ride tr_arg){
		ride_neighbours.push_back(tr_arg);
	}
	void add_flight_step(Flight tr_arg){
		flight_neighbours.push_back(tr_arg);
	}
	

};

struct Previous_node{
	Step node;
	Step prev_node;
};

struct Smallest_length{
	Step node;
	int cost;
};

class Trip{
public:
	string travel_type;
	string name_start;
	string name_end;
	vector<Step> all_steps;
	
	vector<Step> not_done_nodes;
	vector<string> returnpath;
	vector<Smallest_length> smallest_length;
	

	vector<string> trein_dijkstra(){
		vector<Previous_node> previous_node;
		//get start node and set variables
		Step start_node;
		int inf = std::numeric_limits<int>::max();
		not_done_nodes = all_steps;
		
		for(unsigned int i = 0; i < all_steps.size(); i++){
			if (all_steps[i].name == name_start){
				start_node = all_steps[i];
				Smallest_length temp = {all_steps[i], 0};
				smallest_length.push_back(temp);
			}
			else{
				Smallest_length temp = {all_steps[i], inf};
				smallest_length.push_back(temp);
			}
			Previous_node temp2 = {all_steps[i]};
			previous_node.push_back(temp2);
		}
		
		while (not_done_nodes.size() > 0){
			//find smallest yet to be checked node
			Smallest_length minnode;
			for(unsigned int i = 0; i < smallest_length.size(); i++){
				if(not_done_nodes[0].name == smallest_length[i].node.name){
					minnode = smallest_length[i];
					break;
				}
			}
			for(unsigned int i = 0; i < smallest_length.size(); i++){
				if(smallest_length[i].cost < minnode.cost){
					for(unsigned int j = 0; j < not_done_nodes.size(); j++){
						if(not_done_nodes[j].name == smallest_length[i].node.name){
							minnode = smallest_length[i];
						}
					}
				}
			}
			string childnode;
			int weight;
			int lst_size;
			
			if(travel_type == "ride"){
				lst_size = minnode.node.ride_neighbours.size();
			}
			else if(travel_type == "flight"){
				lst_size = minnode.node.flight_neighbours.size();
			}
			else{
				lst_size = minnode.node.train_neighbours.size();
			}
			
			for(unsigned int i = 0; i < lst_size; i++){
				if(travel_type == "ride"){
					childnode = minnode.node.ride_neighbours[i].name_end;
					weight = minnode.node.ride_neighbours[i].kilometer;
				}
				else if(travel_type == "flight"){
					childnode = minnode.node.flight_neighbours[i].name_end;
					weight = minnode.node.flight_neighbours[i].cost;
				}
				else{
					childnode = minnode.node.train_neighbours[i].name_end;
					weight = minnode.node.train_neighbours[i].duration_min;
				}

				
				Smallest_length tempdest;
				for(unsigned int j = 0; j < smallest_length.size(); j++){
					if(childnode == smallest_length[j].node.name){
						tempdest = smallest_length[j];
					}
				}
				if(weight + minnode.cost < tempdest.cost){
					for(unsigned int k = 0; k < previous_node.size(); k++){
						if(previous_node[k].node.name == childnode){
							previous_node[k].prev_node = minnode.node;
						}
					}
					for(unsigned int k = 0; k < smallest_length.size(); k++){
						if(smallest_length[k].node.name == childnode){
							smallest_length[k].cost = weight + minnode.cost;
						}
					}
				}
			}
			int removepos;
			for(unsigned int k = 0; k < not_done_nodes.size(); k++){
				if(not_done_nodes[k].name == minnode.node.name){
					removepos = k;
				}
			}
			not_done_nodes.erase(not_done_nodes.begin()+removepos);
			
		}
		
		//make path
		string current_node = name_end;
		while (current_node != name_start){
			returnpath.insert(returnpath.begin(), current_node);
			for(unsigned int k = 0; k < previous_node.size(); k++){
				if (previous_node[k].node.name == current_node){
					current_node = previous_node[k].prev_node.name;
				}
			}
		}
		returnpath.insert(returnpath.begin(), name_start);
		return returnpath;

	}
};



int main(int argc, char **argv)
{
	Train tr_ab = {"A", "B", 2};
	Train tr_ac = {"A", "C", 5};
	
	Train tr_ba = {"B", "A", 2};
	Train tr_bd = {"B", "D", 9};
	
	Train tr_ca = {"C", "A", 5};
	Train tr_ce= {"C", "E", 2};
	
	Train tr_db = {"D", "B", 9};
	Train tr_df = {"D", "F", 3};
	
	Train tr_ec = {"E", "C", 2};
	Train tr_ef = {"E", "F", 3};
	
	Train tr_fd = {"F", "D", 3};
	Train tr_fe = {"F", "E", 3};
	
	Train tr_be = {"B", "E", 7};
	
	Step tr_A = {"A"};
	tr_A.add_train_step(tr_ab);
	tr_A.add_train_step(tr_ac);
	
	Step tr_B = {"B"};
	tr_B.add_train_step(tr_ba);
	tr_B.add_train_step(tr_bd);
	tr_B.add_train_step(tr_be);
	
	Step tr_C = {"C"};
	tr_C.add_train_step(tr_ca);
	tr_C.add_train_step(tr_ce);
	
	Step tr_D = {"D"};
	tr_D.add_train_step(tr_db);
	tr_D.add_train_step(tr_df);
	
	Step tr_E = {"E"};
	tr_E.add_train_step(tr_ec);
	tr_E.add_train_step(tr_ef);
	
	Step tr_F = {"F"};
	tr_F.add_train_step(tr_fd);
	tr_F.add_train_step(tr_fe);
	
	Trip trip_train = {"train", "A", "F", {tr_A, tr_B, tr_C, tr_D, tr_E, tr_F}};
	vector<string> train_path = trip_train.trein_dijkstra();
	
	for(unsigned int i = 0; i < train_path.size(); i++){
		cout << train_path[i] << " -> ";
		
	}
}
