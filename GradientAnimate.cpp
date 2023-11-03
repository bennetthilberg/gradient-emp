#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>

emp::web::Document doc{"target"};

const int num_h_boxes = 10;
const int num_w_boxes = 15;
const double RECT_SIDE = 25;
const double width{num_w_boxes * RECT_SIDE};
const double height{num_h_boxes * RECT_SIDE};
std::vector<std::vector<int>> cells;

emp::web::Canvas canvas{width, height, "canvas"};

class CAAnimator : public emp::web::Animate {
  private:
    double number = 0;
    std::vector<std::vector<float>> cells;
    double frameCount = 0;
  public:
    CAAnimator() {
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");
        cells.resize(25, std::vector<float>(25, 0));
    }
    void DoFrame() override {
        canvas.Clear();
        number += 0.1;
        
        for (double i = 0; i < 25; i++) {
            for (double j = 0; j < 25; j++) {
                double ijSum = i + j;
                ijSum *= frameCount;
                ijSum += frameCount*frameCount;
                double ijMod = fmod(ijSum, 50.0);
                
                canvas.Rect(i * 10, j * 10, 10, 10, emp::ColorHSV(0, 0, ijMod/49 ), "black");
                
            }
        }
        frameCount++;
    }
    
};

CAAnimator animator;

int main() {
    animator.Step();
}