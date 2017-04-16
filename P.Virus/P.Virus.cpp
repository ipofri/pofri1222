#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int id, size, origin;
	node* parent;
	node* child;
	node* next;
	node* hash;
}*pnode;

const int PN = 10007;
pnode root;
pnode HASH[PN];
pnode find_node(pnode p, int id);
int init();
int insert(int pid, int id, int size);
pnode insert_node(pnode p, pnode n);
pnode insert_hash(pnode p, pnode n);
int remove(int id);
pnode remove_node(pnode p, int id);
int move(int pid, int id);
int gSize;
int gCount;
int CalSizeCount(pnode n);
int CalSizeCount_all(pnode p);
int inspect(int id);
void inspect_node(pnode p, int size);
int recover(int id);
void recover_node(pnode p);
int display_tree(pnode n, int depth);
pnode create_node(int id, int size);

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	root = create_node(1000, 0);

	HASH[root->id % PN] =  root;

	srand(3);
	int N, id, pid, size, cmd;
	int ret;
	pnode n;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d %d %d", &pid, &id, &size, &cmd);
		switch (cmd)
		{
		case 0: //insert
			ret = insert(pid, id, size);
			display_tree(root, 1);
			break;
		case 1: //remove
			ret = remove(id);
			display_tree(root, 1);
			break;
		case 2: //move
			ret = move(pid, id);
			display_tree(root, 1);
			break;
		case 3: //inspect
			ret = inspect(id);
			display_tree(root, 1);
			break;
		case 4: //recover
			ret = recover(id);
			display_tree(root, 1);
			break;
		case 5: //init
			ret = init();
			break;
		}

		getchar();
	}

	init();
	return 0;
}

pnode create_node(int id, int size)
{
	pnode tmp;
	tmp = (pnode)malloc(sizeof(node));
	tmp->parent = NULL; tmp->child = NULL; tmp->next = NULL; tmp->hash = NULL;
	tmp->id = id;
	tmp->size = size;
	tmp->origin = size;
	return tmp;
}
int init()
{
	root->child = NULL;
	pnode tmp;
	for (int i = 0; i < PN; i++)
	{
		while (HASH[i] != NULL)
		{
			tmp = HASH[i]->hash;
			free(HASH[i]);
			HASH[i] = tmp;
		}
		HASH[i] = NULL;
	}

	root = create_node(1000, 0);

	return 0;
}
pnode find_node(pnode p, int id)
{
	if (p == NULL) return p;

	if (p->id == id)
		return p;
	else
		return find_node(p->next, id);
}
pnode find_hash(pnode p, int id)
{
	if (p == NULL) return p;

	if (p->id == id)
		return p;
	else
		return find_node(p->hash, id);
}
int insert(int pid, int id, int size)
{
	pnode node = create_node(id, size);

	node->parent = find_hash(HASH[pid % PN], pid);
	node->id = id;
	node->size = size;
	node->origin = size;

	HASH[id % PN] = insert_hash(HASH[id % PN], node);
	node->parent->child = insert_node(node->parent->child, node);

	return CalSizeCount(node);
}
pnode insert_node(pnode p, pnode n)
{
	n->next = p;
	return n;
}
pnode insert_hash(pnode p, pnode n)
{
	n->hash = p;
	return n;
}
int remove(int id)
{
	pnode n = find_hash(HASH[id / PN], id);
	pnode p = n->parent;

	p->child = remove_node(p->child, id);
	return CalSizeCount(p);
}
pnode remove_node(pnode p, int id)
{
	if (p == NULL) return p;
	if (p->id == id)
	{
		return p->next;
	}
	else
	{
		p->next = remove_node(p->next, id);
		return p;
	}
}
int move(int pid, int id)
{
	pnode n = find_hash(HASH[id%PN], id);
	pnode old_p = n->parent;
	old_p->child = remove_node(old_p->child, id);

	pnode new_p = find_hash(HASH[pid%PN], pid);
	new_p = insert_node(new_p, n);
	return CalSizeCount(new_p);
}
int CalSizeCount(pnode n)
{
	gSize = 0;
	gCount = 0;

	if (n->size != 0)
	{
		gSize = n->size;
		gCount = 1;
	}
	else
	{
		CalSizeCount_all(n);
	}
	
	return gSize;
}
int CalSizeCount_all(pnode n)
{
	if (n == NULL) return gSize;
	CalSizeCount_all(n->child);
	if (n->size != 0)
	{
		gSize += n->size;
		gCount += 1;
	}
	CalSizeCount_all(n->next);

	return gSize;
}

int inspect(int id)
{
	pnode n = find_hash(HASH[id%PN], id);

	CalSizeCount(n);
	int addSize = gSize / gCount;

	if (n->size != 0)
		n->size += addSize;
	else
		inspect_node(n, addSize);

	return CalSizeCount(n);
}
void inspect_node(pnode n, int size)
{
	if (n == NULL) return ;
	inspect_node(n->child, size);
	if (n->size != 0)
	{
		n->size += size;
	}
	inspect_node(n->next, size);
}
int recover(int id)
{
	pnode n = find_hash(HASH[id%PN], id);

	if (n->size != 0)
		n->size = n->origin;
	else
		recover_node(n);

	return CalSizeCount(n);
}

void recover_node(pnode n)
{
	if (n == NULL) return;
	recover_node(n->child);
	if (n->size != 0)
	{
		n->size = n->origin;
	}
	recover_node(n->next);
}
int display_tree(pnode n, int depth)
{
	if (n == NULL)
		return 0;

	for (int i = 0; i < depth; i++)
		printf("\t");
	int iSize = CalSizeCount(root);
	if (n->id == 1000)
		n->size = iSize;
	printf("%d[%d]\n", n->id, n->size);
	display_tree(n->child, depth + 1);
	display_tree(n->next, depth);

}