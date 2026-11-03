#include "TelemetryGenerator.h"
#include "TelemetryPacket.h"
#include "TelemetryProcessor.h"
#include "ThreadSafeQueue.h"

#include <atomic>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

// Satellite Telemetry Processing System
// -------------------------------------
// A multithreaded producer-consumer pipeline:
//   * Producer thread  : generates simulated satellite telemetry packets.
//   * Consumer thread  : processes packets and raises alerts on anomalies.
// The two threads communicate through a bounded, thread-safe queue.
//
// Demonstrates: modern C++ (C++17), smart pointers, RAII, std::thread,
// std::atomic, templates, and a clean multi-file/CMake project layout.

int main(int argc, char** argv) {
    const int packetsToSend = (argc > 1) ? std::stoi(argv[1]) : 200;

    std::cout << "Satellite Telemetry Processing System\n";
    std::cout << "Simulating " << packetsToSend << " telemetry packets...\n\n";

    // Shared queue owned via a smart pointer to show modern memory management.
    auto queue = std::make_shared<ThreadSafeQueue<TelemetryPacket>>(64);
    auto processor = std::make_unique<TelemetryProcessor>();

    std::atomic<int> producedCount{0};

    // ---- Producer thread ----
    std::thread producer([queue, packetsToSend, &producedCount] {
        TelemetryGenerator generator(/*satelliteId=*/7);
        for (int i = 0; i < packetsToSend; ++i) {
            queue->push(generator.next());
            producedCount.fetch_add(1, std::memory_order_relaxed);
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
        queue->close();  // signal the consumer that the stream has ended
    });

    // ---- Consumer thread ----
    std::thread consumer([queue, &processor] {
        while (auto packet = queue->pop()) {
            processor->process(*packet);
        }
    });

    producer.join();
    consumer.join();

    std::cout << "\nProduced " << producedCount.load() << " packets total.";
    processor->printSummary();
    return 0;
}
