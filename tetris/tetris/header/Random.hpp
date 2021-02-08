#pragma once

#ifndef RANDOM_HPP
#define RANDOM_HPP
#include <random>

using namespace std;

/* �����Z���k�E�c�C�X�^�𗐐�������Ƃ��Ďg�p */
random_device rnd_dev; /* �V�[�h�l�����߂�f�o�C�X���� */
mt19937 mt(rnd_dev()); /* �����Z���k�E�c�C�X�^ */
uniform_real_distribution<> dist(0, 1); /* [0, 1]�̈�l���� */

/* ��l�����̐��� */
inline double rnd() {
	return dist(mt);
}

#endif