#include <stdio.h>
#include <stdlib.h>

struct link
{
	int data;
	struct link *next;
};

void add_to_end_of_list(struct link **head, int data);
void print_list(struct link *current);
void free_list(struct link *current);
void delete_end_of_list(struct link **head);
void add_to_start_of_list(struct link **head, int data);

void add_to_end_of_list(struct link **head, int data)
{
	struct link *current = *head;
	if (current != NULL)
		while (current->next != NULL)
			current = current->next;

	struct link *new = malloc(sizeof(struct link));
	if (new == NULL)
	{
		fprintf(stderr, "malloc() failed\n");
		exit(1);
	}
	new->next = NULL;
	new->data = data;

	if (*head == NULL)
		*head = new;
	else
		current->next = new;
}

void print_list(struct link *current)
{
	while (current != NULL)
	{
		printf("%d\n", current->data);
		current = current->next;
	}
}

void free_list(struct link *current)
{
	if (current != NULL)
	{
		free_list(current->next);
		free(current);
	}
}

void delete_end_of_list(struct link **head)
{
	if (*head == NULL)
	{
		fprintf(stderr, "Can't delete the last member of an empty list\n");
		exit(1);
	}
	if ((*head)->next == NULL)
	{
		free(*head);
		*head = NULL;
		return;
	}
	struct link *current = *head;
	while (current->next->next != NULL)
		current = current->next;
	free(current->next);
	current->next = NULL;
}

void add_to_start_of_list(struct link **head, int data)
{
	struct link *new = malloc(sizeof(struct link));
	if (new == NULL)
	{
		fprintf(stderr, "malloc() failed\n");
		exit(1);
	}
	new->next = *head;
	new->data = data;
	*head = new;
}

struct link *search(struct link *head, int data)
{
	while (head != NULL)
	{
		if (head->data == data)
			return head;
		head = head->next;
	}
	return NULL;
}

int main()
{
	struct link *head = NULL;
	int tmp;
	while (scanf("%d", &tmp) != EOF)
		add_to_end_of_list(&head, tmp);
	//  while(scanf("%d",&tmp)!=EOF) add_to_start_of_list(&head,tmp);
	delete_end_of_list(&head);
	print_list(head);
	struct link *tmp_link = search(head, 3);
	if (tmp_link != NULL)
		printf("3 found at %p\n", tmp_link);
	else
		printf("3 not found\n");
	free_list(head);
	return 0;
}
