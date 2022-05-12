#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct st_student {
    int st_id; //학번
    int seat; //자리
    int time; //시간 
    int penalty; //신고 수
};

void printAllSeats(int s[25]); 
int addNewSeat(struct st_student* st[], int s[25], int size);
int editSeat(struct st_student* st[], int s[25], int size); 
int deleteSeat(struct st_student* st[], int s[25], int size);

int main(void) {
	int no;	// 작업번호 
	struct st_seat* students[25];
    int seats[25] = {0,}; // 전체 자리, 0 - 비어있음, 1 - 사용 중
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
			count = addNewSeat(students, seats, count);
		}
		else if(no == 3){ 
			printf(">> 3. 자리 변경 또는 시간 연장\n");
			editSeat(students, seats, count);
		}
		else if(no == 4){
			printf(">> 4. 시간 종료 또는 자리 취소\n");
		    deleteSeat(students, seats, count);
		}
		else break;
	}
	return 0;
}

void printAllSeats(int s[25]) {
    printf("0 : 비어있음, 1 : 현재 사용 중\n");
    for (int i = 1; i <= 25; i++) {
        if (i % 5 == 1) printf("--------------------------------------------\n");
        printf(" %d : %d |", i, s[i-1]);
        if(i % 5 == 0) printf("\n");
        
    }
    printf("--------------------------------------------\n");
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
            break;
        }
    }

    st[size] = d;
    return size+1;
}

int editSeat(struct st_student* st[], int s[25], int size) {
    struct st_student* d;
    int id_temp, seat_temp, choice, tf;

    while (1) {
        tf = 0;
        getchar();
        printf("학번을 입력하세요 > ");
        scanf("%d", &id_temp);

        for (int i = 0; i < size; i++) {
            if (st[i]->st_id == id_temp) {
                d = st[i];
                tf = 1;
            }
        }
        if (tf == 0) printf("입력하신 학번이 존재하지 않습니다. 다시 입력하세요\n");
        else break;
    }

    printf("\n학번: %d, 자리: %d, 예약시간: %d ~ %d\n");
    printf("자리를 변경하시겠습니까 혹은 시간을 연장하시겠습니까?(자리 변경 : 1, 시간 연장 : 2): ");
    scanf("%d", &choice);

    if (choice == 1) { //자리 변경
        while(1) {
            printf("변경할 자리를 입력해주세요 ");
            scanf("%d", &seat_temp);
            if (d->seat == seat_temp) {
                printf("동일한 자리입니다. 시간을 연장하겠습니까?(네 : 1, 아니요 : 0) ");
                scanf("%d", &tf);
                if (tf == 1) break;
                else printf("다시 입력하세요\n");
            }
            else break;
        }
    }
    else { //시간 연장

    }

    return 1;
}

int deleteSeat(struct st_student* st[], int s[25], int size) {
    struct st_student* d;
    int id_temp;

    while (1) {
        int tf = 0;
        printf("학번을 입력하세요 > ");
        scanf("%d", &id_temp);

        for (int i = 0; i < size; i++) {
            if (st[i]->st_id == id_temp) {
                d = st[i];
                tf = 1;
            }
        }
        if (tf == 0) printf("학번이 존재하지 않습니다. 다시 입력하세요\n");
        else break;
    }

	d->seat = -1;
	return size-1;
}
