#pragma once
namespace BW {
	class Timer {
		public:
		Timer();
		~Timer();

		void reset();

		/* Get the time elapsed since start()*/
		double getTime();


		private:
		double start_time;
	};
}

