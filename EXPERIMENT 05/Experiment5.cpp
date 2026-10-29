#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

struct Result { std::string student; int score; char grade = '?'; };
char gradeFor(int score) {
    if (score >= 90) return 'A';
    if (score >= 75) return 'B';
    if (score >= 50) return 'C';
    return 'F';
}
int main() {
    std::vector<Result> results{{"Aswath",88}, {"Student 2",94}, {"Student 3",67}, {"Student 4",42}};
    std::transform(results.begin(), results.end(), results.begin(), [](Result result) {
        result.grade = gradeFor(result.score); return result;
    });
    std::sort(results.begin(), results.end(), [](const Result& a, const Result& b) {
        return a.score > b.score;
    });
    const int total = std::accumulate(results.begin(), results.end(), 0,
        [](int running, const Result& result) { return running + result.score; });
    const auto distinction = std::find_if(results.begin(), results.end(),
        [](const Result& result) { return result.score >= 90; });
    std::cout << "Grade analysis (highest score first)\n";
    for (const auto& result : results)
        std::cout << result.student << " | " << result.score << " | " << result.grade << '\n';
    std::cout << "Total: " << total << "\nAverage: " << std::fixed << std::setprecision(2)
              << static_cast<double>(total) / static_cast<double>(results.size()) << '\n';
    if (distinction != results.end()) std::cout << "First distinction: " << distinction->student << '\n';
}
