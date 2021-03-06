﻿#include <bangtal>
using namespace bangtal;

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	
	SoundPtr sound = Sound::create("Sounds/There Are Chirping Birdies In My Soul - Reed Mathis.mp3");
	SoundPtr taDa = Sound::create("Sounds/Ta Da.mp3");

	ScenePtr scene = Scene::create("방", "Images/방.png");

	// 시작 및 종료 버튼, 아기, 말풍선과 지시어 등 기본 환경 설정
	auto ObjectX = 700, ObjectY = 440;
	ObjectPtr bubble = Object::create("Images/말풍선.png", scene, ObjectX-100, ObjectY-140, false);
	bubble->setScale(0.4f);

	ObjectPtr chicken = Object::create("Images/치킨.png", scene, ObjectX, ObjectY, false);
	chicken->setScale(0.2f);
	ObjectPtr chicken_p = Object::create("Images/치킨.png", scene, ObjectX+1000, ObjectY, false);
	chicken_p->setScale(0.2f);

	ObjectPtr dog = Object::create("Images/강아지.png", scene, ObjectX, ObjectY-10, false);
	dog->setScale(0.2f);
	ObjectPtr dog_p = Object::create("Images/강아지.png", scene, ObjectX + 1000, ObjectY + 1000, false);
	dog_p->setScale(0.2f);

	ObjectPtr rice = Object::create("Images/밥.png", scene, ObjectX, ObjectY, false);
	rice->setScale(0.05f);
	ObjectPtr rice_p = Object::create("Images/밥.png", scene, ObjectX + 1000, ObjectY + 1000, false);
	rice_p->setScale(0.05f);

	ObjectPtr love = Object::create("Images/사랑.png", scene, ObjectX, ObjectY-20, false);
	love->setScale(0.2f);
	ObjectPtr love_p = Object::create("Images/사랑.png", scene, ObjectX + 1000, ObjectY + 1000, false);
	love_p->setScale(0.2f);

	ObjectPtr spoon = Object::create("Images/숟가락.png", scene, ObjectX, ObjectY, false);
	spoon->setScale(0.2f);
	ObjectPtr spoon_p = Object::create("Images/숟가락.png", scene, ObjectX + 1000, ObjectY + 1000, false);
	spoon_p->setScale(0.2f);


	auto problem = chicken;
	auto answer = chicken;

	ObjectPtr baby = Object::create("Images/아기.png", scene, 370, 140);

	auto startButton = Object::create("Images/start.png", scene, 590, 70);
	auto endButton = Object::create("Images/result.png", scene, 590, 20, false);
	auto playButton = Object::create("Images/play.png", scene, 590, 20, false);
	auto offButton = Object::create("Images/end.png", scene, 590, 20, false);

	//점수에 따라 달라지는 말풍선 배정
	auto score0 = Object::create("Images/말풍선0.png", scene, 590, 160, false);
	auto score1 = Object::create("Images/말풍선1.png", scene, 590, 160, false);
	auto score2 = Object::create("Images/말풍선2.png", scene, 590, 160, false);
	auto score3 = Object::create("Images/말풍선3.png", scene, 590, 160, false);
	auto score4 = Object::create("Images/말풍선4.png", scene, 590, 160, false);
	auto score5 = Object::create("Images/말풍선5.png", scene, 590, 160, false);
	score0->setScale(0.7f);
	score1->setScale(0.7f);
	score2->setScale(0.7f);	
	score3->setScale(0.7f);
	score4->setScale(0.7f);
	score5->setScale(0.7f);


	//게임 시작 버튼을 누르면 지시어가 뜨고 타이머가 실행된다. 재시작하는 경우도 고려하여 모든 값들 초기화.
	auto time = 0.5f;
	auto runTime = 30.f;
	auto timer1 = Timer::create(time);
	auto timer2 = Timer::create(time);
	auto timer3 = Timer::create(time);
	auto timer4 = Timer::create(time);
	auto timer5 = Timer::create(time);
	auto backTimer = Timer::create(runTime);
	auto niceTimer = Timer::create(1.f);

	auto round = 1;
	auto correct = 0;
	auto clickToNext = false;
	auto fail = false;

	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		sound->play(true);
		startButton->hide();
		offButton->hide();
		bubble->show();

		score0->hide();
		score1->hide();
		score2->hide();
		score3->hide();
		score4->hide();
		score5->hide();

		round = 1;  //첫번째 판
		correct = 0;
		clickToNext = false;
		fail = false;

		showMessage("'치킨'이라고 말해보자! *알맞은 그림이 뜰 때 아기를 클릭하세요");

		answer = chicken;

		timer1->start();
		backTimer->set(runTime);
		backTimer->start();
		showTimer(backTimer);
		clickToNext = true;

		return true;
		});

	// 다섯 가지 그림이 time 간격으로 바뀜
		timer1->setOnTimerCallback([&](TimerPtr) -> bool {
			chicken->hide();
			dog->show();

			chicken_p->drop();
			dog_p->pick();

			answer = dog;

			timer5->set(time);
			timer2->start();


			return true;
			});

		timer2->setOnTimerCallback([&](TimerPtr) -> bool {
			dog->hide();
			rice->show();

			dog_p->drop();
			rice_p->pick();

			answer = rice;

			timer1->set(time);
			timer3->start();

			return true;
			});

		timer3->setOnTimerCallback([&](TimerPtr) -> bool {
			rice->hide();
			love->show();

			rice_p->drop();
			love_p->pick();

			answer = love;

			timer2->set(time);
			timer4->start();

			return true;
			});

		timer4->setOnTimerCallback([&](TimerPtr) -> bool {
			love->hide();
			spoon->show();

			love_p->drop();
			spoon_p->pick();

			answer = spoon;

			timer3->set(time);
			timer5->start();

			return true;
			});

		timer5->setOnTimerCallback([&](TimerPtr) -> bool {
			spoon->hide();
			chicken->show();

			spoon_p->drop();
			chicken_p->pick();

			answer = chicken;

			timer4->set(time);
			timer1->start();
			return true;
			});
	

	//아기를 클릭하면 정답 여부를 알려주고 정답 개수 카운트
	baby->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (clickToNext == true && round <7 && problem == answer) {
			showMessage("성공!");
			correct++;
			round++;
			clickToNext = false;
		}
		else if (clickToNext == true && round < 7 && problem != answer) {
			showMessage("실패!");
			round++;
			clickToNext = false;

		}	


		timer1->stop();
		timer2->stop();
		timer3->stop();
		timer4->stop();
		timer5->stop();
		if (fail == false && clickToNext == false && round < 6) playButton->show();
		if (fail == false && clickToNext == false && round == 6) {endButton->show(); backTimer->stop();}

		return true;
		});
		
	//다섯 가지 문제를 진행해주는 버튼
	playButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		playButton->hide();
		chicken->hide();
		chicken_p->drop();

		dog->hide();
		dog_p->drop();

		rice->hide();
		rice_p->drop();

		love->hide();
		love_p->drop();

		spoon->hide();
		spoon_p->drop();

		if (round == 2) {
			problem = dog;  showMessage("이번에는 '강아지'라고 말해보자!");
		}
		if (round == 3) {
			problem = rice; showMessage("'밥'이라고 말해보자!");
		}
		if (round == 4) {
			problem = love; showMessage("'사랑'이라고 말해보자!");
		}
		if (round == 5) {
			problem = spoon; showMessage("마지막으로 '숟가락'이라고 말해보자!");
		}

		clickToNext = true;

		answer = chicken;
		timer1->start();


		return true;
		});

	//타이머 종료 시 실패
	backTimer->setOnTimerCallback([&](TimerPtr) -> bool {
		showMessage("앗, 시간 내에 말을 가르치지 못했어요!");
		sound->stop();
		startButton->setImage("Images/restart.png");
		startButton->show();
		offButton->show();

		clickToNext = false;
		fail = true;

		timer1->stop();
		timer2->stop();
		timer3->stop();
		timer4->stop();
		timer5->stop();
		return true;
		});

	//endButton은 현재 RESULT의 기능. 점수를 확인하고 다시 시작할 수 있다.
	endButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endButton->hide();
		bubble->hide();
		sound->stop();
		offButton->show();
		startButton->setImage("Images/restart.png");
		startButton->show();

		//점수에 따라 다른 말풍선이 나타난다.
		if (correct == 0) score0->show();
		if (correct == 1) score1->show();
		if (correct == 2) score2->show();
		if (correct == 3) score3->show();
		if (correct == 4) score4->show();
		if (correct == 5) {
			score5->show(); niceTimer->start(); taDa->play(true);
		niceTimer->setOnTimerCallback([&](TimerPtr) -> bool {
			taDa->stop();
			return true;
			});
		}

		return true;
		});


	offButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();

		return true;
		});

	startGame(scene);


	return 0;
}