#pragma once

#include "Complex.h"

namespace jw {

	template <class T>
	class MandelbrotSet
	{
	private:

		T reStart;
		T reEnd;
		T imStart;
		T imEnd;

		int width = 600;
		int height = 400;

		int maxIter = 80;

	public:
		MandelbrotSet() {
			InitView();
		};

		void InitView() {
			double ratio = (double)width / (double)height;

			reStart = (T)-3.5;
			reEnd = (T)2.5;
			imStart = (T)-((abs(reStart) + abs(reEnd)) * 1.0 / ratio / 2.0);
			imEnd = (T)((abs(reStart) + abs(reEnd)) * 1.0 / ratio / 2.0);
		}

		int MandelbrotTest(const Complex<T> *c) {

			Complex<T> *z = new Complex<T>(0, 0);
			int iter = 0;
			while (z->Modulus() <= (T)2.0 && iter < maxIter) {
				z->Squared()->Sum(c);
				iter++;
			}
			delete z;
			return iter;
		}

		int** DrawMandelbrot() {

			int** set = new int*[width];

			for (int x = 0; x < width; x++) {

				set[x] = new int[height];

				for (int y = 0; y < height; y++) {

					Complex<T> *c = new Complex<T>(reStart + ((T)x / (T)width)  * (reEnd - reStart),
						imStart + ((T)y / (T)height) * (imEnd - imStart));

					set[x][y] = MandelbrotTest(c);

					delete c;
				}
			}

			return set;
		}

		void ZoomIn(int x, int y) {

			T rx, iy;

			rx = (T)x / (T)width;
			iy = (T)y / (T)height;

			T rlen = (reEnd - reStart);
			T ihei = (imEnd - imStart);

			rx = reStart + rx * rlen;
			iy = imStart + iy * ihei;

			reStart = rx - rlen / (T)3;
			reEnd = rx + rlen / (T)3;
			imStart = iy - ihei / (T)3;
			imEnd = iy + ihei / (T)3;
		}

		int Width() {
			return this->width;
		}

		int Height() {
			return this->height;
		}

		int MaxIter() {
			return this->maxIter;
		}

		void SetWidth(int width) {
			this->width = width;
		}

		void SetHeight(int height) {
			this->height = height;
		}

		void SetMaxIter(int maxIter) {
			this->maxIter = maxIter;
		}
	};

}