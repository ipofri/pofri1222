#include <iostream>

using namespace std;

typedef struct st
{
	int age;//0~20
	int passenger;//2~12
	int engine;//1000~5000
	int price;//10000~40000
} CAR;

const int TS = 10;
const int MC = 10000;// 10000;

void build_car(CAR &car)
{
	car.age = rand() % 21;
	car.passenger = rand() % 11 + 2;
	car.engine = rand() % 4000 + 1000;
	car.price = rand() % 30000 + 10000;
}
void buy_car(CAR car);
void sort_age(int from, int to);
void sort_pass(int from, int to);
void sort_eng(int from, int to);
void sort_pri(int from, int to);
int sell_car();
void refund(int order_no);
int empty_car();

int main()
{
	srand(3);
	CAR tmpCar;
	int order_no = 0;//�뷫 100ȸ
	int save_order_no = -1;

	for (int tc = 1; tc <= 10; tc++)
	{
		for (int mc = 1; mc <= MC; mc++)
		{
			build_car(tmpCar);
			buy_car(tmpCar);

			if (rand() % 10 == 0)
			{
				sort_age(rand() % 21, rand() % 21);
				sort_pass(rand() % 11 + 2, rand() % 11 + 2);
				sort_eng(rand() % 4000 + 1000, rand() % 4000 + 1000);
				sort_pri(rand() % 30000 + 10000, rand() % 30000 + 10000);
				order_no = sell_car();

				if (rand() % 10 == 0)
					save_order_no = order_no;

				if (rand() % 100 == 0)
				{
					if (save_order_no != -1)
					{
						refund(save_order_no);
						save_order_no = -1;
					}
				}
			}
		}

		printf("TC#%d = %d", tc, empty_car());
	}

	return 0;
}

//__________________________________________________________________________________________________________________________.


typedef struct node
{
	int id;
	int value;
	node* left;
	node* right;
}*pnode;

enum insert_opt
{
	DEF_ID,
	DEF_VAL,
};

pnode insert_node(pnode p, pnode n, int opt)
{
	if (p == NULL)
		return n;

	if (opt == DEF_ID)//id
	{
		if (n->id < p->id)
			p->left = insert_node(p->left, n, opt);
		else
			p->right = insert_node(p->right, n, opt);
	}
	else
	{
		if (n->value < p->value)
			p->left = insert_node(p->left, n, opt);
		else
			p->right = insert_node(p->right, n, opt);
	}

	return p;
}

pnode search_node(pnode p, int id, int opt)
{
	if (p == NULL)
		return p;

	if (opt == DEF_ID)
	{
		if (p->id == id)
			return p;

		if (id < p->id)
			return search_node(p->left, id, opt);
		else
			return search_node(p->right, id, opt);
	}
	else
	{
		if (p->value == id)
			return p;

		if (id < p->value)
			return search_node(p->left, id, opt);
		else
			return search_node(p->right, id, opt);
	}
}

pnode find_min_node(pnode p)
{
	pnode cur = p;

	while (1)
	{
		if (cur->left == NULL)
			break;
		cur = cur->left;
	}

	return cur;
}

pnode delete_node(pnode p, int id, int opt)
{
	if (p == NULL)
		return NULL;

	if (opt == DEF_ID)
	{
		if (id < p->id)
			p->left = delete_node(p->left, id, opt);
		else if (id > p->id)
			p->right = delete_node(p->right, id, opt);
		else
		{
			if (p->left == NULL)
			{
				pnode tmp = p->right;
				free(p);
				return tmp;
			}
			else if (p->right == NULL)
			{
				pnode tmp = p->left;
				free(p);
				return tmp;
			}
			else
			{
				pnode tmp = find_min_node(p->right);
				p->value = tmp->value;
				p->id = tmp->id;
				p->right = delete_node(p->right, tmp->id, opt);
			}
		}
	}
	else
	{
		if (id < p->value)
			p->left = delete_node(p->left, id, opt);
		else if (id > p->value)
			p->right = delete_node(p->right, id, opt);
		else
		{
			if (p->left == NULL)
			{
				pnode tmp = p->right;
				free(p);
				return tmp;
			}
			else if (p->right == NULL)
			{
				pnode tmp = p->left;
				free(p);
				return tmp;
			}
			else
			{
				pnode tmp = find_min_node(p->right);
				p->value = tmp->value;
				p->id = tmp->id;
				p->right = delete_node(p->right, tmp->value, opt);
			}
		}
	}

	return p;
}

void delete_all(pnode p)
{
	if (p == NULL)
		return;

	delete_all(p->left);
	delete_all(p->right);
	free(p);
}

typedef enum FILTER
{
	AGE = 1,
	PASS,
	ENG,
	PRI,
	MAX_FILTER,
};

pnode filter[MAX_FILTER] = { NULL, };
int gidx = 1;
char id_list[10002] = { 0, };

void buy_car(CAR car)
{
	pnode tmp[MAX_FILTER];
	tmp[AGE] = (pnode)malloc(sizeof(node));
	tmp[AGE]->value = car.age; tmp[AGE]->id = gidx;
	tmp[AGE]->left = NULL; tmp[AGE]->right = NULL;
	filter[AGE] = insert_node(filter[AGE], tmp[AGE], DEF_VAL);

	tmp[PASS] = (pnode)malloc(sizeof(node));
	tmp[PASS]->value = car.passenger; tmp[PASS]->id = gidx;
	tmp[PASS]->left = NULL; tmp[PASS]->right = NULL;
	filter[PASS] = insert_node(filter[PASS], tmp[PASS], DEF_VAL);

	tmp[ENG] = (pnode)malloc(sizeof(node));
	tmp[ENG]->value = car.engine; tmp[ENG]->id = gidx;
	tmp[ENG]->left = NULL; tmp[ENG]->right = NULL;
	filter[ENG] = insert_node(filter[ENG], tmp[ENG], DEF_VAL);

	tmp[PRI] = (pnode)malloc(sizeof(node));
	tmp[PRI]->value = car.price; tmp[PRI]->id = gidx;
	tmp[PRI]->left = NULL; tmp[PRI]->right = NULL;
	filter[PRI] = insert_node(filter[PRI], tmp[PRI], DEF_VAL);

	gidx++;
}


void swap(int& from, int& to)
{
	if (from > to)
	{
		int tmp = from;
		from = to;
		to = tmp;
	}
}
enum tra_type
{
	DEF_CREATE,
	DEF_MODIFY,
};

pnode filter_list = NULL;
void traverse_filter(pnode p, int from, int to, int opt)
{
	if (p == NULL)
		return;

	if (from < p->value)
	{
		traverse_filter(p->left, from, to, opt);
	}

	if (from <= p->value && p->value <= to)
	{
		if (opt == DEF_CREATE)
		{
			pnode tmp;
			tmp = (pnode)malloc(sizeof(node));
			tmp->value = 1; tmp->id = p->id;
			tmp->left = NULL; tmp->right = NULL;
			filter_list = insert_node(filter_list, tmp, DEF_ID);
		}
		else
		{
			pnode tmp = search_node(filter_list, p->id, DEF_ID);
			if (tmp != NULL)
				tmp->value += 1;
		}
	}

	if (to >= p->value)
	{
		traverse_filter(p->right, from, to, opt);
	}
}
void sort_age(int from, int to)
{
	swap(from, to);
	int type = AGE;

	//id�� value�� order list�� �����.
	traverse_filter(filter[type], from, to, DEF_CREATE);
}
void sort_pass(int from, int to)
{

}
void sort_eng(int from, int to)
{

}
void sort_pri(int from, int to)
{}
int sell_car()
{
	return 0;
}
void refund(int order_no)
{}
int empty_car()
{
	//delete_all(root_id);

	return 0;
}