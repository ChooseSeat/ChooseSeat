#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct st_seat {
    int st_number; //학번
    int seat; //자리
    //int 
    int penalty; //신고 수
};

void printAllSeats(struct st_seat* s[], int size); 
int addNewSeat(struct st_seat* s[], int size);
void editSeat(struct st_seat* s[], int size); 
void deleteSeat(struct st_seat* s[], int size);

int main(void) {
	int no;	// 작업번호 
	struct st_seat* seats[25];
	int count = 0; // 전체 예약자리 수

	while(1){
		printf("\n[작업] 1.전체 자리 조회 2.자리 예약 3.자리 변경 또는 시간 연장 4.시간 종료 또는 자리 취소 0.종료\n");
		printf("작업 번호는? > ");
		scanf("%d", &no);

		if(no == 1){ 
			printf(">> 1.전체 자리 조회 (총 %d과목)\n", count);
			printAllSeats(seats, count);
		}
		else if(no == 2){ 
			printf(">> 2.자리 예약\n");
			count = addNewSeat(seats, count);
		}
		else if(no == 3){ 
			printf(">> 3.자리 변경 또는 시간 연장\n");
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

void printAllSeats(struct st_seat* s[], int size); 
int addNewSeat(struct st_seat* s[], int size);
void editSeat(struct st_seat* s[], int size); 
void deleteSeat(struct st_seat* s[], int size);
