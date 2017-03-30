#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int id; //1000~1,000,000,000
	int size;
	int origin;
	node* left;
	node* right;
	node* parent; 
	node* files_child;
} *pnode;

pnode root = NULL;

pnode delete_node(pnode p, int id);

void delete_files(pnode p)//file 정보를 지우고, root에서 id를 지운다.
{
	if (p == NULL)
		return;

	delete_files(p->left);
	delete_files(p->right);

	delete_files(search_node(root, p->files_child->id)->files_child);

	free(p);

	delete_node(root, p->id);
}

void init()
{
	if (root != NULL)
	{
		delete_files(root);
	}
	root = (pnode)malloc(sizeof(node));

	root->id = 1000;
	root->size = 0;
	root->origin = 0;
	root->left = NULL;
	root->right = NULL;
	root->parent = NULL;
	root->files_child = NULL;
}

pnode add_node(pnode p, pnode n)
{
	if (p == NULL)
		return n;
	
	if (n->id < p->id)
		p->left = add_node(p->left, n);
	else
		p->right = add_node(p->right, n);

	return p;
}

int cal_folder_size(pnode n)//folder의 크기를 구함 
{
	if (n == NULL)
		return 0;

	int size;
	if (n->size > 0)
		size = n->size;
	else
		size = cal_folder_size(n->files_child);

	size += cal_folder_size(n->left);
	size += cal_folder_size(n->right);

	return size;
}

int cal_file_count(pnode n)
{
	if (n == NULL)
		return 0;

	int size;
	if (n->size > 0)
		size = 1;
	else
		size = cal_file_count(n->files_child);

	size += cal_folder_size(n->left);
	size += cal_folder_size(n->right);

	return size;
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

void copy_node(pnode src, pnode tar)
{
	tar->id = src->id;
	tar->size = src->size;
	tar->origin = src->origin;
	tar->left = src->left;
	tar->right = src->right;
	tar->parent = src->parent;
	tar->files_child = src->files_child;
}

pnode delete_node(pnode p, int id)
{
	if (p == NULL)
		return p;
	else if (id < p->id)
		p->left = delete_node(p->left, id);
	else if (id > p->id)
		p->right = delete_node(p->right, id);
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

		pnode tmp = find_min_node(p->right);
		copy_node(tmp, p);
		p->right = delete_node(p->right, tmp->id);
	}

	return p;
}

pnode search_node(pnode p, int id)
{
	if (p == NULL)
		return p;

	if (p->id == id)
		return p;
	else if (id < p->id)
		return search_node(p->left, id);
	else
		return search_node(p->right, id);
}

void add(int id, int pid, int size)
{
	//pid를 찾고 id를 추가한다.
	pnode temp = (node*)malloc(sizeof(node));
	temp->id = id;
	temp->size = size;
	temp->origin = size;
	temp->parent = search_node(root, pid);
	temp->left = NULL;
	temp->right = NULL;
	temp->files_child = NULL;

	root = add_node(root, temp);

	pnode file = (node*)malloc(sizeof(node));
	copy_node(temp, file);
	
	file->parent->files_child = add_node(file->parent->files_child, file);
}

int move(int pid, int id)
{
	pnode n = search_node(root, id);
	pnode old_parent = n->parent;
	pnode tmp = (pnode)malloc(sizeof(node));
	copy_node(search_node(old_parent->files_child, id), tmp);
	delete_node(old_parent->files_child, id);

	pnode p = search_node(root, pid);
	add_node(p->files_child, tmp);

	return cal_folder_size(p);
}

int delete_id(int id)
{
	pnode n = search_node(root, id);
	pnode p = n->parent;
	p = delete_node(p, id);

	delete_files(n->files_child);

	root = delete_node(root, id);

	return cal_folder_size(p);
}

void infect_node(pnode n, int size)
{
	if (n == NULL)
		return;

	if (n->size > 0)
		n->size += size;
	else
		infect_node(search_node(root, n->id), size);

	infect_node(n->left, size);
	infect_node(n->right, size);
}

int infect(int id)
{
	pnode n = search_node(root, id);
	pnode p = n->parent;

	if (n->size > 0)//file
	{
		n = search_node(p, id);
		n->size *= 2;
	}
	else
	{
		int size = cal_folder_size(n->files_child) / cal_file_count(n->files_child);

		infect_node(n->files_child, size);
	}

	int temp;
	if (n->size > 0)
	{
		temp = n->size;
	}
	else
	{
		temp = cal_folder_size(n->files_child);
	}
	return temp;
}

int recover_node(pnode n)
{
	if (n == NULL)
		return;

	if (n->size > 0)
		n->size = n->origin;
	else
		infect_node(n->files_child);

	recover_node(n->left);
	recover_node(n->right);
}

int recover(int id)
{
	pnode n = search_node(root, id);
	pnode p = n->parent;

	if (n->size > 0)//file
	{
		n = search_node(p, id);
		n->size = n->origin;
	}
	else
	{
		recover_node(n->files_child);
	}

	int temp;
	if (n->size > 0)
	{
		temp = n->size;
	}
	else
	{
		temp = cal_folder_size(n->files_child);
	}
	return temp;
}

int main()
{
	srand(3);

	int a = sizeof(node);
	int b = a;
}