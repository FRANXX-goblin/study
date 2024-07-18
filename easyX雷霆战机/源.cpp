#include<graphics.h>
#include<conio.h>
#include<time.h>
IMAGE myplaneimg[2], enemyplaneimg[2], mymissileimg[2], enemymissileimg[2];
ExMessage msg;
struct myplane {
	int x;
	int y;
	int width;
	int length;
	int cerx;
	int cery;
	int cerwidth;
	int cerlength;
	int speed;
	int HP;
};
struct myplane myplane= {575,575,50,50,595,595,10,10,20,5};
struct enemyplane {
	int x = 0;
	int y = 0;
	int width = 34;
	int length = 50;
	int cerx = 0;
	int cery = 0;
	int cerwidth = 16;
	int cerlength = 20;
	int speed = 1;
	int HP = 1;
	struct enemyplane* next = NULL;
}ene;
struct mymissile{
	int x = 0;
	int y = 0;
	int width = 10;
	int length = 20;
	int speed = 1;
	int atc = 1;
	struct mymissile *next=NULL;
}my;
void prepare() {
	loadimage(myplaneimg + 0, "./res/myplane/myplane.jpg", myplane.width, myplane.length);
	loadimage(myplaneimg + 1, "./res/myplane/myplanebk.jpg", myplane.width, myplane.length);
	loadimage(enemyplaneimg + 0, "./res/enemyplane/enemyplane.jpg", ene.width, ene.length);
	loadimage(enemyplaneimg + 1, "./res/enemyplane/enemyplanebk.jpg", ene.width, ene.length);
	loadimage(mymissileimg + 0, "./res/myattack/mymissile.jpg",my.width ,my.length);
	loadimage(mymissileimg + 1, "./res/myattack/mymissilebk.jpg", my.width, my.length);
	initgraph(1200, 800);
}
void drawmyplane() {
	putimage(myplane.x, myplane.y, myplaneimg + 0, SRCAND);
	putimage(myplane.x, myplane.y, myplaneimg + 1, SRCPAINT);
}
void movemyplane() {
	int keydown = _getch();
	switch (keydown){
	case 'w':
	case 'W':
	case 72:
		if (myplane.y > 40) {
			myplane.y -= myplane.speed;
			myplane.cery -= myplane.speed;
		}
		break;
	case's':
	case'S':
	case 80:
		if (myplane.y < 750) {
			myplane.y += myplane.speed;
			myplane.cery += myplane.speed;
		}
		break;
	case'a':
	case'A':
	case 75:
		if (myplane.x > 0) {
			myplane.x -= myplane.speed;
			myplane.cerx -= myplane.speed;
		}
		break;
	case'd':
	case'D':
	case 77:
		if (myplane.x < 1150) {
			myplane.x += myplane.speed;
			myplane.cerx += myplane.speed;
		}
		break;
	}
}
struct mymissile* mmphead = new (struct mymissile);
struct mymissile *mmpf = mmphead,*mmp = NULL;
void myfire(){
		mmp = new(struct mymissile);
		mmpf->next = mmp;
		mmp->x = myplane.x + 20;
		mmp->y = myplane.y - 20;
		mmp->next = NULL;
		mmpf = mmp;
}
struct mymissile* deletemp(struct mymissile* mp) {
	struct mymissile* p = mmphead;
	while (p != NULL && p->next != NULL) {
		if (p->next == mp) {
			p->next = mp->next;
			delete(mp);
			mp = p->next;
			return mp;
		}
		p = p->next;
	}
}
void drawMoveDeletemymissile() {
	struct mymissile* mp = mmphead->next;
	if (mp != NULL) {
		while (mp!=NULL&&mp->next != NULL) {
			if(mp->y<=0){
				mmphead->next = mp->next;
				mp=deletemp(mp);
			}
			else {
				putimage(mp->x, mp->y, mymissileimg + 0, SRCAND);
				putimage(mp->x, mp->y, mymissileimg + 1, SRCPAINT);
				mp->y -= mp->speed;
				mp = mp->next;
			}
		}
	}
}
struct enemyplane* enephead=new(struct enemyplane);
struct enemyplane* enepf=enephead,*enep=NULL;
void creatEnemy() {
	enep = new(struct enemyplane);
	enepf->next = enep;
	enep->x = rand()%1167;
	enep->y = 0;
	enep->cerx = enep->x + 9;
	enep->cery = enep->y + 15;
	enepf = enep;
}
void moveEnemy() {
	struct enemyplane* ep = enephead->next;
	if(ep!=NULL){
		while (ep->next != NULL) {
			if (ep->y >= 800) {
				ep->y = 0;
				ep = enephead->next;
			}
			else {
				ep->y += ep->speed;
				ep->cery += ep->speed;
				ep = ep->next;
			}
		}
	}
}
void drawEnemy() {
	struct enemyplane* ep = enephead->next;
	if (ep != NULL) {
		while (ep->next != NULL) {
				putimage(ep->x, ep->y, enemyplaneimg + 0, SRCAND);
				putimage(ep->x, ep->y, enemyplaneimg + 1, SRCPAINT);
				ep = ep->next;
		}
	}
}
struct enemyplane* deleteep(struct enemyplane* ep) {
	struct enemyplane* p = enephead;
	while (p->next != NULL) {
		if (p->next == ep) {
			p->next = ep->next;
			delete(ep);
			ep = p->next;
			return ep;
		}
		p = p->next;
	}
}
void hurtDleteEnemy_deleteMymissile() {
	struct mymissile* mp = mmphead->next; 
	struct enemyplane* ep = enephead->next;
	if (mp != NULL && ep != NULL) {
		while (mp!=NULL&&mp->next != NULL) {
			while (ep != NULL && ep->next != NULL) {
				if (ep->HP <= 0) {
					ep=deleteep(ep);
					}
				else {
					if (mp!=NULL&&mp->y - ep->cery <= 20 && mp->x - ep->cerx + my.width >= 0 && mp->x - ep->cerx - ene.cerwidth <= 0) {
						mp=deletemp(mp);
						ep->HP -= my.atc;
					}
					else if (ep->next == NULL) {
						break;
					}
					else {
						ep = ep->next;
					}
				}
			}
			if (mp != NULL)
				mp = mp->next;
		}
	}
}
int Timer(int duration, int id) {
	static int startTime[10];
	int endTime = clock();
	if (endTime - startTime[id] > duration) {
		startTime[id] = endTime;
		return 1;
	}
	return 0;
}
int main() {	
	prepare();
	BeginBatchDraw();
	while (1){
	cleardevice();
	drawmyplane();
	if(_kbhit())
	movemyplane();
	if (Timer(10, 1))
		myfire();
	drawMoveDeletemymissile();
	if (Timer(300, 2))
		creatEnemy();
	if (Timer(10, 3))
		moveEnemy();
	drawEnemy();
	hurtDleteEnemy_deleteMymissile();
	FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
	return 0;
}