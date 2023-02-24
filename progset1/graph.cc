#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <float.h>
// #include <bits/stdc++.h> 
using namespace std; 
  
// Node 
typedef struct node 
{ 
    int data; 
  
    // Lower values indicate 
    // higher priority 
    int priority; 
  
    struct node* next; 
  
} Node; 
  
// Function to create a new node 
Node* newNode(int d, int p) 
{ 
    Node* temp = (Node*)malloc(sizeof(Node)); 
    temp->data = d; 
    temp->priority = p; 
    temp->next = NULL; 
  
    return temp; 
} 
  
// Return the value at head 
int peek(Node** head) 
{ 
    return (*head)->data; 
} 
  
// Removes the element with the 
// highest priority from the list 
void pop(Node** head) 
{ 
    Node* temp = *head; 
    (*head) = (*head)->next; 
    free(temp); 
} 
  
// Function to push according to priority 
void push(Node** head, int d, int p) 
{ 
    Node* start = (*head); 
  
    // Create new Node 
    Node* temp = newNode(d, p); 
  
    // Special Case: The head of list has 
    // lesser priority than new node. So 
    // insert newnode before head node 
    // and change head node. 
    if ((*head)->priority > p) 
    { 
          
        // Insert New Node before head 
        temp->next = *head; 
        (*head) = temp; 
    } 
    else
    { 
          
        // Traverse the list and find a 
        // position to insert new node 
        while (start->next != NULL && 
            start->next->priority < p) 
        { 
            start = start->next; 
        } 
  
        // Either at the ends of the list 
        // or at required position 
        temp->next = start->next; 
        start->next = temp; 
    } 
} 
  
// Function to check is list is empty 
int isEmpty(Node** head) 
{ 
    return (*head) == NULL; 
} 

int main() {

    int n = 1024;
    double graph[n][n];

    for (int i=0; i < n; i++){
        for (int j=i; j<n; j++) {
            double weight = ((double) rand()) / RAND_MAX;
            graph[i][j] = weight;
            graph[j][i] = weight;
        }
    }

    double distance[n];

    for (int i = 0; i < n; i++) {
        distance[i] = DBL_MAX;
    }

    int prev[n];
    distance[0] = 0;
    bool visited[n]; 
    memset( visited, 0, n*sizeof(int) );
    int source = 0;
    
    Node* pq = newNode(source, distance[source]);
  
    while (!isEmpty(&pq)) 
    { 
        int vertex = peek(&pq);
        pop(&pq); 
        visited[vertex] = 1;

        for (int i = 0; i < n; i++) {
            if (visited[i] == 0) {
                if (distance[i] > graph[vertex][i]) {
                    distance[i] = graph[vertex][i];
                    prev[i] = vertex;
                    
                    if (isEmpty(&pq)) {
                        pq = newNode(i, distance[i]);
                    }

                    else {
                        push(&pq, i, distance[i]);
                    }
                }
            }
        }
    } 

    double sum = 0;
    for (int i=0; i<n; i++) {
        sum += distance[i];
    }

    int count[n];
    memset( count, 0, n*sizeof(int) );

    printf("%.3f\n", sum);

    for (int i=0; i<n;i++) {
        printf("%i ", visited[i]);
    }

    // for (int i=0; i<n;i++) {
    //     printf("%i ", count[i]);
    // }

    return 0; 

    
}
