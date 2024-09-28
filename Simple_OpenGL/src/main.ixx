export module main;

import std;
import engine;

export
int main(int argc, char** argv) {
	LogDebug("Starting application: {}", argv[0]);
	LogInfo("Starting application: {}", argv[0]);
	LogWarning("Starting application: {}", argv[0]);
	LogError("Starting application: {}", argv[0]);

	std::ofstream out("log.txt");
	FLogDebug(out, "Starting application: {}", argv[0]);
	FLogInfo(out, "Starting application: {}", argv[0]);
	FLogWarning(out, "Starting application: {}", argv[0]);
	FLogError(out, "Starting application: {}", argv[0]);

	Vec2f a(0.5, 1), b(2, 3);

	if ((a + b).x == 2.5) {
		std::cout << "Hello, World! B\n";
	}

	if (((Vec2i)a).x == 0) {
		std::cout << "Hello, World! B\n";
	}

	std::cout << a.x << " " << a.y << "\n";
	std::cout << a[0] << " " << a[1] << "\n";

	auto c = a + b;
	c += b;
	std::cout << c.x << " " << c.y << "\n";

	std::cout << a[2] << "\n"; // Should assert

	return 0;
}