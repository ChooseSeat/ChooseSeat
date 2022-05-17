#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct st_student {
    int seat; //자리
    int st_id; //학번
    int month; //시간
    int day; 
    int hour; 
    int min; 
    int penalty; //신고 수
    int ismark; //0은 아직 도착 안함, 1은 도착
};

int loadData(struct st_student* st[]);

void printAllSeats(int s[25]); 
int addNewSeat(struct st_student* st[], int s[25], int size, struct tm *);
int editSeat(struct st_student* st[], int s[25], int size, struct tm *); 
int deleteSeat(struct st_student* st[], int s[25], int size);

int markIn(struct st_student* st[], int s[25], int size, struct tm *);
int extendSeat(struct st_student* st[], int s[25], int size, struct tm *);
int reportSeat(struct st_student* st[], int s[25], int size);
void searchSeat(struct st_student* st[], int s[25], int size);

int saveData(struct st_student* st[], int size); 

int main(void) {
	int no, count = 0;	// 작업번호 
	struct st_student* students[25];
    int seats[25] = {0,}; // 전체 자리, 0 - 비어있음, 1 - 사용 중
	
    time_t current;
    time(&current);
    struct tm *t = localtime(&current);
  
    count = loadData(students);  // 전체 예약자리 수
    for (int i = 0; i < count; i++) {
      seats[students[i]->seat - 1] = 1;
      printf("%d %d %d %d %d %d %d %d\n", students[i]->seat, students[i]->st_id, students[i]->month, students[i]->day, students[i]->hour, students[i]->min, students[i]->ismark, students[i]->penalty);
      //printf("%d  ", students[i]->penalty);
    }
  
    printf("%d개 예약 존재\n", count);

  while(1){
		printf("\n[작업] 1.전체 자리 조회 2.자리 예약 3.자리 변경 4. 시간 종료 또는 자리 취소 5. 도착 확인 6.시간 연장 7. 신고하기 8. 검색하기 0.저장 및 종료\n");
		printf("작업 번호는? > ");
		scanf("%d", &no);

        if (no == 0) {
            int issave = saveData(students, count);
            if (issave == 1) printf("저장이 완료되었습니다.");
            break;
        }
		else if(no == 1){ 
			printf(">> 1. 전체 자리 조회 (잔여석 %d)\n", 25 - count);
			printAllSeats(seats);
		}
	  else if(no == 2){ 
			printf(">> 2. 자리 예약\n");
			count = addNewSeat(students, seats, count, t);
		}
		else if(no == 3){ 
			printf(">> 3. 자리 변경\n");
			int ised = editSeat(students, seats, count, t);
      if (ised == 1) printf("자리가 변경되었습니다.\n");
		}
		else if(no == 4){
			printf(">> 4. 시간 종료 또는 자리 취소\n");
		  deleteSeat(students, seats, count);
      printf("자리가 삭제되었습니다.\n");
		} //여기까지 확인
    else if(no == 5){ 
			printf(">> 5. 도착 확인하기\n");
		  int ismark = markIn(students, seats, count, t);
      if (ismark == 1) printf("도착 확인이 완료되었습니다. 열공!\n");
		}
    else if(no == 6){
			printf(">> 6. 시간 연장\n");
		  int isext = extendSeat(students, seats, count, t);
      if (isext == 1) printf("자리가 연장되었습니다.\n");
		}
        else if(no == 7){
			printf(">> 7. 신고하기\n");
		    int isrepo = reportSeat(students, seats, count);
        if (isrepo == 1) printf("신고가 완료되었습니다\n");
		}
        else if(no == 8){
			printf(">> 8. 검색하기\n");
		    searchSeat(students, seats, count);
		}
	}
	return 0;
}

int loadData(struct st_student* st[]) {
    int count=0;
	FILE* file;

	file=fopen("seats.txt", "r");
	while(!feof(file)){
		st[count] = (struct st_student*)malloc(sizeof(struct st_student));
		int r = fscanf(file, "%d %d %d %d %d %d %d %d", &(st[count]->seat), &(st[count]->st_id), &(st[count]->month), &(st[count]->day), &(st[count]->hour), &(st[count]->min), &st[count]->ismark, &(st[count]->penalty));
		if(r < 7) break;
		count++;
	}
	fclose(file);
	return count;
}

void printAllSeats(int s[25]) {
    printf("0 : 비어있음, 1 : 현재 사용 중\n");
    for (int i = 1; i <= 25; i++) {
        if (i % 5 == 1) printf("--------------------------------------------\n");
        printf(" %2d : %d |", i, s[i-1]);
        if(i % 5 == 0) printf("\n");
        
    }
    printf("--------------------------------------------\n");
}

int addNewSeat(struct st_student* st[], int s[25], int size, struct tm * t) {
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
            d->ismark = 0;
            d->month = t->tm_mon + 1;
            d->day = t->tm_mday;
            d->hour = t->tm_hour;
            d->min = t->tm_min;
            d->penalty = 0;
            d->ismark = 0;
            s[num-1] = 1;
            break;
        }
    }

    st[size] = d;
    return size+1;
}

int editSeat(struct st_student* st[], int s[25], int size, struct tm * t) {
    struct st_student* d;
    int id_temp, seat_temp, tf, temp;

    while (1) {
        tf = 0;
        getchar();
        printf("학번을 입력하세요 > ");
        scanf("%d", &id_temp);

        for (int i = 0; i < size; i++) {
            if (st[i]->st_id == id_temp) {
                d = st[i];
                tf = 1;
                temp = i;
            }
        }
        if (tf == 0) printf("입력하신 학번이 존재하지 않습니다. 다시 입력하세요\n");
        else break;
    }

    while(1) {
      printf("변경할 자리를 입력해주세요 ");
      scanf("%d", &seat_temp);
      if (d->seat == seat_temp) printf("동일한 자리입니다. 다시 입력하세요\n");
      else {
        if (s[seat_temp - 1] == 1) printf("현재 사용중인 자리입니다. 다시 입력하세요\n");
        else {
          s[d->seat-1] = 0;
          d->seat = seat_temp;
          d->hour = t->tm_hour;
          d->min = t->tm_min;
          s[seat_temp - 1] = 1;
          return 1;
        }
      }
    }
    return 0;
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
  s[d->seat - 1] = 0;
	d->seat = -1;
	return size;
}

int markIn(struct st_student* st[], int s[25], int size, struct tm * t) { 
  struct st_student* d;
  int id_temp, seat_temp, choice, tf, temp;

  while (1) {
    tf = 0;
    printf("학번을 입력하세요 > ");
    scanf("%d", &id_temp);

    for (int i = 0; i < size; i++) {
      if (st[i]->st_id == id_temp) {
        d = st[i];
        tf = 1;
        temp = i;
      }
    }
    if (tf == 0) printf("입력하신 학번이 존재하지 않습니다. 다시 입력하세요\n");
    else break;
    }

  if (d->min >= 45) { ///
    if ((t->tm_hour == d->hour && t->tm_min < d->min + 15 - 60) || (t->tm_hour == d->hour + 1 && t->tm_min <= 59)) d->ismark = 1;
    else d->ismark = 0;
  }
  else {
    if (t->tm_hour == d->hour && t->tm_min <= d->min + 15) d->ismark = 1;
    else d->ismark = 0;
  }
  return 1;
}

int extendSeat(struct st_student* st[], int s[25], int size, struct tm * t) {
    struct st_student* d;
    int id_temp, seat_temp, choice, tf, temp;

    while (1) {
        tf = 0;
        printf("학번을 입력하세요 > ");
        scanf("%d", &id_temp);

        for (int i = 0; i < size; i++) {
            if (st[i]->st_id == id_temp) {
                d = st[i];
                tf = 1;
                temp = i;
            }
        }
        if (tf == 0) printf("입력하신 학번이 존재하지 않습니다. 다시 입력하세요\n");
        else break;
    }

    if (d->min < 15) { // ex. 11:5까지 예약시간일 경우
      if ((t->tm_hour == d->hour && t->tm_min >= d->min + 60 - 15) || (t->tm_hour == d->hour + 1 && t->tm_min <= d->min)) {
        d->hour = t->tm_hour;
        d->min = t->tm_min;
        return 1;
      }
      else {
        printf("아직 연장 가능 시간이 아닙니다.\n");
        return 0;
      }
    }
        
    else if (d->min == 15) { // ex. 11:15까지 예약시간일 경우
      if (t->tm_hour == d->hour + 1 && t->tm_min <= d->min) {
        d->hour = t->tm_hour;
        d->min = t->tm_min;
        return 1;
      }
      else {
        printf("아직 연장 가능 시간이 아닙니다.\n");
        return 0;
      }
    }
        
    else { // ex. 11:30까지 예약시간일 경우
      if (t->tm_hour == d->hour + 1 && t->tm_min >= d->min - 15 && t->tm_min <= d->min) {
        d->hour = t->tm_hour;
        d->min = t->tm_min;
      }
      else {
        printf("아직 연장 가능 시간이 아닙니다.\n");
        return 0;
      }
    }
  return 1;
}
//자리 
int reportSeat(struct st_student* st[], int s[25], int size) {
  int seat_temp, tf, i;

  printAllSeats(s);
  printf("신고할 자리를 입력해주세요 ");
  scanf("%d", &seat_temp);
  if (s[seat_temp - 1] == 1) {
    printf("%d번을 정말로 신고하시겠습니까? (네 : 1, 아니요 : 0) ", seat_temp);
    scanf("%d", &tf);
    
    if (tf == 1) {
      for (i = 0; i < size; i++) {
        if (seat_temp - 1 == st[i]->seat) break;
      }
      
      st[i-1]->penalty++;
      return 1;
    }
    else return 0;
  }
    
  else {
    printf("%d번은 비어있는 자리입니다. 신고하기가 취소됩니다.\n", seat_temp);
    return 0;
  }
}
//자리 검색
void searchSeat(struct st_student* st[], int s[25], int size) { //자리 번호로 학번과 시간 출력
    int seat_temp, temp, i;

    printAllSeats(s);
    printf("자리 번호를 입력하세요 > ");
    scanf("%d", &seat_temp);
    seat_temp--;

    if (s[seat_temp] == 1) {
      for (i = 0; i < 25; i++) {
        if (seat_temp == st[i]->seat - 1) break;
      }
        printf("\n자리: %d, 학번: %d, 예약시간: %d월 %d일 %d:%d ~ %d:%d\n", st[i]->seat, st[i]->st_id, st[i]->month, st[i]->day, st[i]->hour, st[i]->min, st[i]->hour + 1, st[i]->min);
    }
    else printf("입력하신 자리는 비어있습니다.\n");
}
//데이타 저장 
int saveData(struct st_student* st[], int size) {
    FILE* file;
	file = fopen("seats.txt", "w");
	for(int i = 0; i < size; i++){
        if (st[i]->seat != -1) fprintf(file, "%d %d %d %d %d %d %d %d\n", st[i]->seat, st[i]->st_id, st[i]->month, st[i]->day, st[i]->hour, st[i]->min, st[i]->ismark, st[i]->penalty);
	}
	fclose(file);	
    return 1;
}

