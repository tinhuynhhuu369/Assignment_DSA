// Change direction of prev & next pointer of every customer
			scan = X;
			do {
				customer *node_need_change = scan->prev;
				customer *tmp = scan;
				node_need_change->next = node_need_change->prev;
				node_need_change->prev = tmp;
				scan = scan->next;
			} while (scan != X);