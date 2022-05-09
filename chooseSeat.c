#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct st_student {
    int st_id; //학번
    int seat; //자리
    //int 
    int penalty; //신고 수
};

void printAllSeats(int s[25]); 
int addNewSeat(struct st_student* st[], int s[25], int size);
void editSeat(struct st_student* st[], int s[25], int size); 
void deleteSeat(struct st_student* st[], int s[25], int size);

int main(void) {
	int no;	// 작업번호 
	struct st_seat* students[25];
    int seats[25]; // 전체 자리, 0 - 비어있음, 1 - 사용 중
	int count = 0; // 전체 예약자리 수

	while(1){
		printf("\n[작업] 1.전체 자리 조회 2.자리 예약 3.자리 변경 또는 시간 연장 4.시간 종료 또는 자리 취소 0.종료\n");
		printf("작업 번호는? > ");
		scanf("%d", &no);

		if(no == 1){ 
			printf(">> 1. 전체 자리 조회 (잔여석 %d)\n", 25 - count);
			printAllSeats(seats);
		}
		else if(no == 2){ 
			printf(">> 2. 자리 예약\n");
			count = addNewSeat(seats, count);
		}
		else if(no == 3){ 
			printf(">> 3. 자리 변경 또는 시간 연장\n");
			editSeat(seats, count);
		}
		else if(no == 4){
			printf(">> 4. 시간 종료 또는 자리 취소\n");
		    deleteSeat(seats, count);
		}
		else break;
	}
	return 0;
}

void printAllSeats(int s[25]) {
    printf("0 : 비어있음, 1 : 현재 사용 중\n");
    for (int i = 1; i <= 25; i++) {
        if (i % 5 == 0) printf("\n--------------------------------\n");
        printf("%d : %d |", i, s[i-1]);
        if(i % 5 == 4) printf("\n");
        printf("--------------------------------\n");
    }
}

int addNewSeat(struct st_student* st[], int s[25], int size) {
    struct st_student* d = (struct st_student*)malloc(sizeof(struct st_student));
    int num;

    while(1) {
        printAllSeats(s);
        printf("학번을 입력하세요 > ");
        scanf("%d", &d->st_id);
        printf("예약할 자리를 입력하세요 > ");
        scanf("%d", &num);
        if (s[num - 1] == 1) printf("이미 사용 중인 자리입니다. 다시 입력해주세요\n");
        else {
            d->seat = num;
            s[num-1] = 1;
        }
    }

    st[size] = d;
    return size+1;
}

void editSeat(struct st_student* st[], int s[25], int size) {

}

void deleteSeat(struct st_student* st[], int s[25], int size) {

}
