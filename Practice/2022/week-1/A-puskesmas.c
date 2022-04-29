/**
 * fundamental code written by : Bayu Laksana
 * @date 2019-02-29
 * 
 * @editor Daud Dhiya' Rozaan
 * @date 2022-03-12
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct pqueueNode_t {
    char name[10], sick[25];
    struct pqueueNode_t *next;
} PQueueNode;

typedef struct pqueue_t {
    PQueueNode *_top;
    unsigned _size;
} PriorityQueue;

void pqueue_init(PriorityQueue *pqueue){
    pqueue->_top = NULL;
    pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) {
    return (pqueue->_top == NULL);
}

/**
 * pqueue_push_ruang() function is function to push the patient to the room,
 * actually this function is just like pushing to queue, without priority
 */
void pqueue_push_ruang(PriorityQueue *pqueue, char name[], char sick[]){
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = (PQueueNode*) malloc (sizeof(PQueueNode));
    strcpy(newNode->name, name);
    strcpy(newNode->sick, sick);
    newNode->next = NULL;

    if (pqueue_isEmpty(pqueue)) {
        pqueue->_top = newNode;
        return;
    }
    else{
        while(temp->next != NULL)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

/**
 * pqueue_push() function is function to push the patient to the pqueue,
 * priority is determined lexicographically from patient name in ascending order
 */
void pqueue_push(PriorityQueue *pqueue, char name[], char sick[]){
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = (PQueueNode*) malloc (sizeof(PQueueNode));
    strcpy(newNode->name, name);
    strcpy(newNode->sick, sick);
    newNode->next = NULL;

    if (pqueue_isEmpty(pqueue)) {
        pqueue->_top = newNode;
        return;
    }
 
    short i = 0, j = 0, k, len = strlen(name);
    while (pqueue->_top->name[i] == name[i])
        i++;

    if(pqueue->_top->name[i] > name[i]){
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
    }
    else{
        for(k=0;k<len;k++){
            while (temp->next != NULL && temp->next->name[j] < name[j])
                temp = temp->next;
            while (temp->next != NULL && temp->next->name[j] == name[j])
                j++;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void pqueue_pop(PriorityQueue *pqueue){
    if(!pqueue_isEmpty(pqueue)) {
        PQueueNode *temp = pqueue->_top;
        pqueue->_top = pqueue->_top->next;
        free(temp);
    }
}

// to get top->name in pqueue
char* pqueue_topname(PriorityQueue *pqueue) {
    if(!pqueue_isEmpty(pqueue))
        return pqueue->_top->name;
    else return 0;
}

// to get top->sick in pqueue
char* pqueue_topsick(PriorityQueue *pqueue) {
    if(!pqueue_isEmpty(pqueue))
        return pqueue->_top->sick;
    else return 0;
}

int main(int argc, char const *argv[]){
    /**
     * create (and init) pqueue object for doctor_room (myPque), 
     * patient_queue, and for every disease
     */
    PriorityQueue myPque, antrian,
                sakit_pusing, sakit_diare, sakit_maag, sakit_flu;
    pqueue_init(&myPque);
    pqueue_init(&antrian);
    pqueue_init(&sakit_pusing);
    pqueue_init(&sakit_diare);
    pqueue_init(&sakit_maag);
    pqueue_init(&sakit_flu);

    short ruang, q, 
        pasien = 0, pusing = 0, diare = 0, flu = 0, maag = 0; // flag to count patient with each disease
    char nama[10], penyakit[25];
    
    scanf("%hi", &ruang);
    while(scanf("%hi", &q)!=EOF){
        switch(q){
            case 1:
                getchar();
                scanf("%s %s", nama, penyakit);
                
                /**
                 * if patient is still less than available room,
                 * patient enters the room
                 */
                if(pasien < ruang){
                    if(strcmp(penyakit, "pusingkebanyakantugas")==0)
                        pusing++;
                    else if(strcmp(penyakit, "diare")==0)
                        diare++;
                    else if(strcmp(penyakit, "maag")==0)
                        maag++;
                    else if(strcmp(penyakit, "flu")==0)
                        flu++;

                    pqueue_push_ruang(&myPque, nama, penyakit);
                    printf("Pasien atas nama %s terdaftar ke database.\n", nama);
                    pasien++;
                    
                    printf("Pasien atas nama %s langsung masuk.\n", nama);
                }
                /**
                 * if patient is more than available room,
                 * patient enters to the queue.
                 * Priority is determined by the level of disease as described in the problem
                 */
                else{
                    if(strcmp(penyakit, "pusingkebanyakantugas")==0){
                        pqueue_push(&sakit_pusing, nama, penyakit);
                        pusing++;
                    }
                    else if(strcmp(penyakit, "diare")==0){
                        pqueue_push(&sakit_diare, nama, penyakit);
                        diare++;
                    }
                    else if(strcmp(penyakit, "maag")==0){
                        pqueue_push(&sakit_maag, nama, penyakit);
                        maag++;
                    }
                    else if(strcmp(penyakit, "flu")==0){
                        pqueue_push(&sakit_flu, nama, penyakit);
                        flu++;
                    }
                        
                    printf("Pasien atas nama %s terdaftar ke database.\n", nama);
                    printf("Pasien atas nama %s mengantri.\n", nama);
                    // every case 1 is completed, the number of patients is increases
                    pasien++;
                }
            break;
                
            default: // case 2:
                if(!pqueue_isEmpty(&myPque)){ // if in the room is not empty
                    printf("Pasien atas nama %s sudah selesai konsultasi mengenai %s.\n", 
                            pqueue_topname(&myPque), pqueue_topsick(&myPque));
                    pqueue_pop(&myPque);
                    
                    /**
                     * if patient is still more than available room,
                     * that mean there will be patient who entered from pqueue to the room
                     */
                    if(pasien>ruang){
                        /**
                         * Priority is determined by the level of disease as described in the problem.
                         * Take the top->name and top->sick by available function
                         */
                        if(!pqueue_isEmpty(&sakit_pusing)){
                            printf("Pasien atas nama %s masuk dari antrian.\n", pqueue_topname(&sakit_pusing));
                            pqueue_push_ruang(&myPque, pqueue_topname(&sakit_pusing), pqueue_topsick(&sakit_pusing));
                            pqueue_pop(&sakit_pusing);
                        }
                        else if(!pqueue_isEmpty(&sakit_diare)){
                            printf("Pasien atas nama %s masuk dari antrian.\n", pqueue_topname(&sakit_diare));
                            pqueue_push_ruang(&myPque, pqueue_topname(&sakit_diare), pqueue_topsick(&sakit_diare));
                            pqueue_pop(&sakit_diare);
                        }
                        else if(!pqueue_isEmpty(&sakit_maag)){
                            printf("Pasien atas nama %s masuk dari antrian.\n", pqueue_topname(&sakit_maag));
                            pqueue_push_ruang(&myPque, pqueue_topname(&sakit_maag), pqueue_topsick(&sakit_maag));
                            pqueue_pop(&sakit_maag);
                        }
                        else if(!pqueue_isEmpty(&sakit_flu)){
                            printf("Pasien atas nama %s masuk dari antrian.\n", pqueue_topname(&sakit_flu));
                            pqueue_push_ruang(&myPque, pqueue_topname(&sakit_flu), pqueue_topsick(&sakit_flu));
                            pqueue_pop(&sakit_flu);
                        }
                    }
                    // every case 2 is completed, the number of patients is reduced
                    pasien--;
                }
                else continue;
            break;
        }
    }
    // print the patient data today
    printf("Data pasien hari ini:\n");
    if(diare>0)
        printf("diare: %hi.\n", diare);
    if(flu>0)
        printf("flu: %hi.\n", flu);
    if(maag>0)
        printf("maag: %hi.\n", maag);
    if(pusing>0)
        printf("pusingkebanyakantugas: %hi.\n",pusing);

    return 0;
}