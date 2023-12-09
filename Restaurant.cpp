#include "main.h"

class list_timing 
{
	public:
			class customer {
			public:	
				string name;
				int energy;
				customer* prev;
				customer* next;
			public:
				customer(){}
				customer(string na, int e, customer* p, customer *ne): name(na), energy(e), prev(p), next(ne){}
				~customer(){}
				void print() {
					cout << name << "-" << energy << endl;
				}
			};

	customer* head;
    customer* tail;
public:
    list_timing() : head(nullptr), tail(nullptr) {}
    ~list_timing()
    {
        customer* current = head;
        while (current != nullptr)
        {
            customer* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
    }

	// DOMAIN -> Delete Node < 0 in list_timing
	void DO_leth_0() {
		customer *scan = tail;
		do {
		if (scan->energy > 0) {
			scan = scan->prev;
			continue;
		}
		customer*tmp = scan;
		if (scan == tail) {tail = tail->prev;}
		else if (scan == head && scan->next == nullptr) {head = tail = nullptr; scan->print(); delete scan; break;}
		else if (scan == head && scan->next != nullptr) {head = head->next;}
		else {
		scan->prev->next = scan->next;
		scan->next->prev = scan->prev;
		scan = scan->prev;
		}
		tmp->print();
		delete tmp;
		} while (scan != nullptr);
	};

	// DOMAIN -> Delete Node > 0 in list_timing
	void DO_grth_0() {
		customer *scan = tail;
		do {
		if (scan->energy < 0) {
			scan = scan->prev;
			continue;
		}
		customer*tmp = scan;
		if (scan == tail) {tail = tail->prev;}
		else if (scan == head && scan->next == nullptr) {head = tail = nullptr; scan->print(); delete scan; break;}
		else if (scan == head && scan->next != nullptr) {head = head->next;}
		else {
		scan->prev->next = scan->next;
		scan->next->prev = scan->prev;
		scan = scan->prev;
		}
		tmp->print();
		delete tmp;
		} while (scan != nullptr);
	};

    // Function to add a new element to list_timing
    void add_customer(string name, int energy)
    {
        if (head == nullptr)
        {
            head = new customer(name, energy, nullptr, nullptr);
            tail = head;
        }
        else
        {
            customer* new_customer = new customer(name, energy, tail, nullptr);
            tail->next = new_customer;
            tail = new_customer;
        }
    };

	// Function to return customer removed and delete it in list_timing
	string get_a_delete() {
		string str = this->head->name;
		customer *tmp = this->head;
		this->head = this->head->next;
		delete tmp;
		return str;
	};

	// Function to reset list when delete list have only 1 element
	void reset_list() {
		customer *tmp = head;
		head = tail = nullptr;
		delete tmp;
	}
};

class imp_res : public Restaurant
{	
	public:
		customer *X;
		customer *first_cus_queue;
		customer *end_cus_queue;
		list_timing list;
	public:	
		imp_res() : X(nullptr), first_cus_queue(nullptr), end_cus_queue(nullptr) {};
		~imp_res() {};
		void swap_node (customer *X, customer *Y) {
			string name_X = X->name;
			int energy_X = X->energy;
			X->name = Y->name;
			X->energy = Y->energy;
			Y->name = name_X;
			Y->energy = energy_X;
			return;
		};
		
		int count_queue(customer *first_cus_queue) {
			if (first_cus_queue == nullptr) return 0;
			else if (first_cus_queue == end_cus_queue) return 1;
			else {
				customer *scan = first_cus_queue;
				int count = 0;
				do {
					count++;
					scan = scan->next;
				} while (scan != nullptr);
				return count;
			}
		};

		int count_customer(customer *X) {
			if (X == nullptr) return 0;
			else if (X->next == X) return 1;
			else {
				customer*scan = X;
				int count = 0;
				do {
					count++;
					scan = scan->next;
				} while (scan != X); 
				return count;
			}
		};

		void RED(string name, int energy)
		{	
			// Flags to remark if add to restaurant instead of queue
			bool flag = true;

			// Energy = 0
			if (energy == 0) return;
			
			// Restaurant and queue full 
			if (count_customer(X) >= MAXSIZE && count_queue(first_cus_queue) >= MAXSIZE) return;

			// Initialize new customer 
			customer *cus = new customer (name, energy, nullptr, nullptr);

			// First customer
			if (X == nullptr) {
				X = cus;
				X->next = X;
				X->prev = X;
				}

			// Second customer
			else if (count_customer(X) == 1) {
				X->next = X->prev = cus;
				cus->next = cus->prev = X;
				X = X->next;
				}
			
			// Third customer or more
			else if (count_customer(X) >= 2 && count_customer(X) < MAXSIZE / 2) {
				if (energy >= X->energy) {
					//sameclockwise
					customer *behind = X->next;
					X->next = behind->prev = cus;
					cus->prev = X;
					cus->next = behind; 
					X = X->next;
				}
				else {
					//counterclockwise
					customer *behind = X->prev;
					X->prev = behind->next = cus;
					cus->next = X;
					cus->prev = behind;
					X = X->prev;
				}
			}

			//Number of customers >= Maxsize/2
			else if (count_customer(X) >= MAXSIZE / 2 && count_customer(X) < MAXSIZE) {
				//Calculate res to decide X position
				int max_res = -1;
				int res_wout_abs = 0;
				string mark_name = "";
				string name = X->name;
				customer *temp = X->next;
				while (temp->name != name) {
					int res = energy - temp->energy;
					if (abs(res) > max_res) {
						max_res = abs(res);
						res_wout_abs = res;
						mark_name = temp->name;
						}
					temp = temp->next;
				}

				//Find X position with mark_name
				customer *X_mn = cus;
				while (X->name != mark_name) {
					X = X->next;
				}

				//Add new customer 
				if (res_wout_abs >= 0) {
					//sameclockwise
					customer *behind = X->next;
					X->next = behind->prev = cus;
					cus->prev = X;
					cus->next = behind; 
					X = X->next;
				}
				else {
					//counterclockwise
					customer *behind = X->prev;
					X->prev = behind->next = cus;
					cus->next = X;
					cus->prev = behind;
					X = X->prev;
				}

				X = X_mn;
			}

			//Add into queue
			else if (count_customer(X) >= MAXSIZE && count_queue(first_cus_queue) < MAXSIZE) {
				//queue empty
				if (count_queue(first_cus_queue) == 0) first_cus_queue = end_cus_queue = cus;
				//queue have >= 1 customer
				else {
					cus->prev = end_cus_queue;
					end_cus_queue->next = cus;
					end_cus_queue = end_cus_queue->next; 
				}
				flag = false;
			}
			
			// Add into list_timing
			if (flag) list.add_customer(name, energy);
		};

		void BLUE(int num)
		{
			// Delete all 
			if (num >= count_customer(X) || num >= MAXSIZE) {
				customer *scan = X->next;
				do {
					customer *delete_node = scan;
					scan = scan->next;
					delete delete_node;
				} while (scan != X);
				X = nullptr;
				return;
			};

			// Delete num node
			for (int i = 1; i <= num; i++) {
				string name_node_delete = list.get_a_delete();
				customer *scan = X;
				while (scan->next->name != name_node_delete) scan = scan->next;
				customer *delete_node = scan->next;
				scan->next = scan->next->next;
				scan->next->prev = scan;
				delete delete_node;
			};
			
			// Add customer into restaurant from queue
			while (count_customer(X) < MAXSIZE && count_queue(first_cus_queue) >= 1) {
				// Add into restaurant
				string name = first_cus_queue->name;
				int energy = first_cus_queue->energy;
				RED(name, energy); 

				// Delete from queue
				if (count_queue(first_cus_queue) == 1) {
					first_cus_queue = end_cus_queue = nullptr;
				}
				else {
					customer *tmp = first_cus_queue;
					first_cus_queue = first_cus_queue->next;
					first_cus_queue->prev = nullptr;
					delete tmp;
				};
			};
		};

		void inssort2(customer* start, int incr) {
			customer* current = start;
			if (!current) return;

			customer* temp = nullptr;
			customer* check = nullptr;

			bool flag = true;
			do {
				flag = true;
				for (int i = incr; i > 0; i--) {
					if (!current) {
						current = start;
						flag = false;
					} else {
						temp = current;
						current = current->next;
					}
				}

				while (check != temp) {
					if (temp->energy < check->energy) {
						swap(temp->name, check->name);
						swap(temp->energy, check->energy);
					}
					check = check->next;
				}
				check = start;
			} while (!flag);
		};

		void shellsort(customer *start, int n) {
    	for (int i = n / 2; i > 2; i /= 2) {
        for (int j = 0; j < i; j++) {
            inssort2(start, i);
        }
    	}
    	inssort2(start, 1);
		};

		void PURPLE()
		{
			// Find position with energy highest 
			customer*scan = first_cus_queue;
			int max = first_cus_queue->energy;
			string name_remark = first_cus_queue->name;
			do {
				if (scan->energy > max) {
					max = scan->energy;
					name_remark = scan->name;
				}
				scan = scan->next;
			}
			while(scan != nullptr);

			// Count how much node 
			int count = 0;
			customer*sub_scan = first_cus_queue;
			while (sub_scan->prev != scan) {
				count++;
				sub_scan = sub_scan->next;
			}

			// Offical shell sort 
			shellsort(first_cus_queue, count);
		};
		void REVERSAL()
		{
			// Change X position
			customer*scan = X->next;
			while (scan->energy * X->energy < 0) scan = scan->next;
			while (this->X != scan) this->X = this->X->next;

			// Change direction of prev & next pointer of every customer
			scan = X;
			do {
				customer *node_need_change = scan->prev;
				customer *tmp = scan->next;
				scan->next = node_need_change; 
				scan->prev = tmp;
				scan = tmp; 
			} while (scan != X);

			// Change remain nodes
			customer*scan_v1 = X->next;
			customer*scan_v2 = X->prev;
			// Count node > 0
			customer*scan_count = X;
			int count = 0;
			do {
				if (scan_count->energy > 0) count++;
				scan_count = scan_count->next;
			} while (scan_count != X);
			// Loop
			for (int i = 1; i <= floor(count/2); i++) {
				while(scan_v1->energy * X->energy > 0) scan_v1 = scan_v1->next;
				while(scan_v2->energy * X->energy > 0) scan_v2 = scan_v2->prev;
				swap_node(scan_v1, scan_v2);
			}
		};

		int sum_sequence(customer*scan, int count) {
			int sum = 0;
			for (int i = 0; i < count; i++) {
				sum += scan->energy;
				scan = scan->next;
			}
			return sum;
		};

		void UNLIMITED_VOID()
		{
			// Dont do anything
			if (count_customer(X) < 4) return;

			//find position
			customer*scan = X;
			int sum_min = 999999999;
			customer*remark_sequence = X;
			int remark_count = 0;
			for (int i = 4; i <= count_customer(X); i++) {
				for (int j = 0; j < i; j++) {
					int sum_tmp = sum_sequence(scan, i);
					if (sum_tmp <= sum_min) {
						sum_min = sum_tmp;
						remark_sequence = scan;
						remark_count = i;
					}
					scan = scan->next;
				}
			}
			
			// print 
			for (int i = 0; i < remark_count; i++) {
				remark_sequence->print();
				remark_sequence = remark_sequence->next;
			}
		};

		void DOMAIN_EXPANSION()
		{	
			//X empty
			if (X == nullptr || count_customer(X) == 1 || (count_customer(X) == 2 && X->energy * X->next->energy > 0)) return;
			else if (count_customer(X) == 2 && X->energy * X->next->energy < 0) {
				if (abs(X->energy) > abs(X->next->energy)) {
					customer*tmp = X->next;
					X->next = X->prev = X;
					tmp->print();
					delete tmp;
				}
			} 
			else {
			// Calculate sum abs of chu thuat & oan linh
			int sum_grthan_0 = 0;
			int sum_lethan_0 = 0;
			customer*scan = X;
			// In restaurant
			do {
				if (scan->energy > 0) sum_grthan_0 += scan->energy;
				else sum_lethan_0 += abs(scan->energy);
				scan = scan->next;
			} while (scan != X);
			// In queue
			scan = first_cus_queue;
			do {
				if (scan->energy > 0) sum_grthan_0 += scan->energy;
				else sum_lethan_0 += abs(scan->energy);
				scan = scan->next;
			}
			while (scan != nullptr);

			// Delete 
			scan = X;

			// Delete node < 0
			if (sum_grthan_0 > sum_lethan_0) {
				// Delete in res
				do {
					if (scan->energy > 0) {
						scan = scan->next;
						continue;
					}
					if (scan == X) {
						if (scan->energy > 0) X = scan->next;
						else X = scan->prev;
					}
					customer* tmp = scan;
					scan = scan->prev;
					scan->next = scan->next->next;
					scan->next->prev = scan;
					delete tmp;
					scan = scan->next;
				} while (scan != X);

				// Print()
				// In queue
				scan = end_cus_queue;
				do {
					if (scan->energy > 0) {
						scan = scan->prev;
						continue;
					}
					if (scan == end_cus_queue) end_cus_queue = end_cus_queue->prev;
					else if (scan == first_cus_queue && scan->next != nullptr) first_cus_queue = first_cus_queue->next;
					else if (scan == first_cus_queue && scan->next == nullptr) {first_cus_queue = end_cus_queue = nullptr; scan->print();delete scan; break;}
					else {
					scan->prev->next = scan->next;
					scan->next->prev = scan->prev;
					}
					customer *tmp = scan;
					scan = scan->prev;
					tmp->print();
					delete tmp;
				} while (scan != nullptr);

				// In list_timing
				list.DO_leth_0(); 
			}

			// Delete node > 0
			else {
				// Delete in res
				do {
					if (scan->energy < 0) {
						scan = scan->next;
						continue;
					}
					if (scan == X) {
						if (scan->energy > 0) X = scan->next;
						else X = scan->prev;
					}
					customer* tmp = scan;
					scan = scan->prev;
					scan->next = scan->next->next;
					scan->next->prev = scan;
					delete tmp;
					scan = scan->next;
				} while (scan != X);

				// Print()
				// In queue
				scan = end_cus_queue;
				do {
					if (scan->energy < 0) {
						scan = scan->prev;
						continue;
					}
					if (scan == end_cus_queue) end_cus_queue = end_cus_queue->prev;
					else if (scan == first_cus_queue && scan->next != nullptr) first_cus_queue = first_cus_queue->next;
					else if (scan == first_cus_queue && scan->next == nullptr) {first_cus_queue = end_cus_queue = nullptr; scan->print();delete scan; break;}
					else {
					scan->prev->next = scan->next;
					scan->next->prev = scan->prev;
					}
					customer *tmp = scan;
					scan = scan->prev;
					tmp->print();
					delete tmp;
				} while (scan != nullptr);

				// In list_timing
				list.DO_grth_0(); 
			}
			}
			

			// Recover customer in restaurant by adding remain customers from queue to restaurant
			// Add customer into restaurant from queue
			while (count_customer(X) < MAXSIZE && count_queue(first_cus_queue) >= 1) {
				// Add into restaurant
				string name = first_cus_queue->name;
				int energy = first_cus_queue->energy;
				RED(name, energy); 

				// Delete from queue
				if (count_queue(first_cus_queue) == 1) {
					first_cus_queue->name = "";
					first_cus_queue->energy = 0;
					end_cus_queue->name = "";
					end_cus_queue->energy = 0;
				}
				else {
					customer *tmp = first_cus_queue;
					first_cus_queue = first_cus_queue->next;
					first_cus_queue->prev = nullptr;
					delete tmp;
				};
			};
		};

		void LIGHT(int num)
		{
			customer *scan = X;
			if (X == nullptr) return;
			if (num > 0) {
				scan = X;
				do {
					scan->print();
					scan = scan->next;
				}
				while (scan != X);
			}
			else if (num < 0) {
				scan = X;
				do {
					scan->print();
					scan = scan->prev;
				}
				while (scan != X);
			}
			// num == 0
			else {
				scan = first_cus_queue;
				do {
					scan->print();
					scan = scan->next;
				} while (scan != nullptr); 
			} 
		};
};