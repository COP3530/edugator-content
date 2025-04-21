.PHONY: fibonacci unique-paths min-cost-climbing-stairs clean help

all: help

fibonacci: fibonacci.cpp
	@echo "🔢 Building fibonacci..."
	@g++ -std=c++14 -o bin/fibonacci fibonacci.cpp

unique-paths: unique-paths.cpp
	@echo "🧭 Building unique-paths..."
	@g++ -std=c++14 -o bin/unique-paths unique-paths.cpp

min-cost-climbing-stairs: min-cost-climbing-stairs.cpp
	@echo "⛰️  Building min-cost-climbing-stairs..."
	@g++ -std=c++14 -o bin/min-cost-climbing-stairs min-cost-climbing-stairs.cpp

clean:
	@echo "🧹 Cleaning build artifacts..."
	@rm -f bin/*

help:
	@echo "✨ Available targets:"
	@echo "   make fibonacci                  Build the fibonacci executable"
	@echo "   make unique-paths               Build the unique-paths executable"
	@echo "   make min-cost-climbing-stairs   Build the min-cost-climbing-stairs executable"
	@echo "   make clean                      Remove all files in bin/"
	@echo "   make help                       Show this help message"
