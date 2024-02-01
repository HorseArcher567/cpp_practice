#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool dataReady = false;

void producer() {
	// 模拟一些工作
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	// 产生数据
	{
		std::lock_guard<std::mutex> lock(mtx);
		dataReady = true;
	}

	// 通知等待的线程
	cv.notify_one();
}

void consumer() {
	std::unique_lock<std::mutex> lock(mtx);

	// 等待条件为真
	cv.wait(lock, [] { return dataReady; });

	// 在条件满足后执行操作
	std::cout << "Consumer: Data is ready!" << std::endl;
}

int main() {
	std::thread producerThread(producer);
	std::thread consumerThread(consumer);

	producerThread.join();
	consumerThread.join();

	return 0;
}
