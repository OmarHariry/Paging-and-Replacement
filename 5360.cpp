#include"5360.h"
vector<int>input;

void solve() {
	int temp;
	int buffersize;
	string policy;
	cin >> buffersize;
	cin >> policy;
	while (cin >> temp && temp!=-1) {
		input.push_back(temp);
	}
	
	if (policy == "FIFO") {
		print_at_begining(policy);
		print_at_end(FIFO_policy(buffersize));
	}
		
	else if (policy == "LRU") {
		print_at_begining(policy);
		print_at_end(LRU_policy(buffersize));
	}
		
	else if (policy == "OPTIMAL") {
		print_at_begining(policy);
		print_at_end(optimal_policy(buffersize));
	}
		
	else if (policy == "CLOCK") {
		print_at_begining(policy);
		print_at_end(clock_policy(buffersize));
	}
}
void print_at_begining(string str) {
	cout << "Replacement Policy = " << str << endl ;
	cout << "-------------------------------------\n";
	cout << "Page   Content of Frames\n";
	cout << "----   -----------------\n";
}
void print_at_end(int fault_counter) {
	cout << "-------------------------------------\n";
	cout << "Number of page faults = " << fault_counter<<"\n";
}
int FIFO_policy(int buffersize) {
	vector<int>buffer;
	unordered_map<int, int>mp;						//map to determine before insertion whether the 
	int fault_counter = 0;							//element already exist or not in the buffer
	bool fault = false;
	bool miss = false;
	int candidate = 0;
	for (int i = 0; i < input.size(); ++i) {
		miss = mp.find(input[i]) == mp.end();				//If this returns true then element doesnt exist
		if (!miss) {
			//do nothing
		}
		else {								//miss and buffer has free space
			if (buffer.size() < buffersize) {
				buffer.push_back(input[i]);
				mp.insert({ input[i],0 });
			}
			else {							//miss and buffer has no space
				++fault_counter;
				fault = true;
				int remove = candidate++ % buffersize;
				mp.erase(buffer[remove]);
				mp.insert({ input[i],0 });
				buffer[remove] = input[i];
			}
		}
		cout << setw(2) << setfill('0') << input[i];
		if (fault) {
			cout << " F";
			cout << "   ";
			fault = false;
		}
		else
			cout << "     ";
		for (auto x : buffer) {
			cout << setw(2) << setfill('0') << x << " ";
		}
		cout << endl;
	}
	return fault_counter;
}
int LRU_policy(int buffersize) {
	//replace input[i] with input[i-buffersize]
	vector<int>buffer;
	unordered_map<int, int>mp;						//map to determine before insertion whether the 
	int fault_counter = 0;							//element already exist or not in the buffer
	bool fault = false;
	bool miss = false;
	for (int i = 0; i < input.size(); ++i) {
		int candidate = i-buffersize;
		miss = mp.find(input[i]) == mp.end();				//If this returns true then element doesnt exist
		if (!miss) {
			//do nothing
		}
		else {
			if (buffer.size() < buffersize) {
				buffer.push_back(input[i]);
				mp.insert({ input[i],0 });
				
			}
			else {
				++fault_counter;
				fault = true;
				int remove = find_index(buffer,candidate);
				mp.erase(buffer[remove]);
				mp.insert({ input[i],0 });
				buffer[remove] = input[i];
	
			}
		}
		cout << setw(2) << setfill('0') << input[i];
		if (fault) {
			cout << " F";
			cout << "   ";
			fault = false;
		}
		else
			cout << "     ";
		for (auto x : buffer) {
			cout << setw(2) << setfill('0') << x << " ";
		}
		cout << endl;
	}
	return fault_counter;
}
int find_index(vector<int>buffer,int candidate) {
	int index;
	int element = input[candidate];
	for (int i = 0; i < buffer.size(); ++i) {
		if (element == buffer[i])
			index = i;
	}
	return index;

}
int optimal_policy(int buffersize) {
	vector<int>buffer;
	unordered_map<int, int>mp;						//map to determine before insertion whether the 
	int fault_counter = 0;							//element already exist or not in the buffer
	bool fault = false;
	bool miss = false;
	for (int i = 0; i < input.size(); ++i) {
		miss = mp.find(input[i]) == mp.end();				//If this returns true then element doesnt exist
		if (!miss) {
			//do nothing
		}
		else {
			if (buffer.size() < buffersize) {
				buffer.push_back(input[i]);
				mp.insert({ input[i],0 });
				
			}
			else {
				++fault_counter;
				fault = true;
				int remove = find_max_index(buffer,i);
				mp.erase(buffer[remove]);
				mp.insert({ input[i],0 });
				buffer[remove] = input[i];
	
			}
		}
		cout << setw(2) << setfill('0') << input[i];
		if (fault) {
			cout << " F";
			cout << "   ";
			fault = false;
		}
		else
			cout << "     ";
		for (auto x : buffer) {
			cout << setw(2) << setfill('0') << x << " ";
		}
		cout << endl;
	}
	return fault_counter;
}
int find_max_index(vector<int>buffer,int start) {
	int index = start + 1, buffer_index;
	for (int i = 0; i < buffer.size(); ++i) {
		for (int j = start + 1; j <= input.size(); ++j) {
			if (j == input.size())
				return i;					//element is no longer used then it will be removed
			else if (buffer[i] == input[j]){
					if (index < j) {
						index = j;
						buffer_index = i;
					}
					break;
			}
		}
	}
	return buffer_index;

}
int clock_policy(int buffersize) {
	vector<int>buffer;
	vector<int>clock;
	unordered_map<int, int>mp;						//map to determine before insertion whether the 
	int fault_counter = 0;							//element already exist or not in the buffer
	bool fault = false;
	bool miss = false;
	int clock_index = 0;
	for (int i = 0; i < buffersize; ++i) {				//initially buffer is filled with clock use = 1
		clock.push_back(1);
	}
	for (int i = 0; i < input.size(); ++i) {
		miss = mp.find(input[i]) == mp.end();				//If this returns true then element doesnt exist
		if (!miss) {
			if (clock[clock_index] == 0) {
				clock[clock_index] = 1;
				clock_index = (clock_index + 1) % clock.size();
			}
		}	
		else {
			if (buffer.size() < buffersize) {
				buffer.push_back(input[i]);
				mp.insert({ input[i],0 });
			}
			else {
				++fault_counter;
				fault = true;
				while (clock[clock_index] == 1) {
					clock[clock_index] = 0;
					clock_index=(clock_index+1)% clock.size();
				}
				mp.erase(buffer[clock_index]);
				mp.insert({ input[i],0 });
				buffer[clock_index] = input[i];
				clock[clock_index] = 1;
				clock_index = (clock_index + 1) % clock.size();
			}
		}
		cout << setw(2) << setfill('0') << input[i];
		if (fault) {
			cout << " F";
			cout << "   ";
			fault = false;
		}
		else
			cout << "     ";
		for (auto x : buffer) {
			cout << setw(2) << setfill('0') << x << " ";
		}
		cout << endl;
	}
	return fault_counter;
}
