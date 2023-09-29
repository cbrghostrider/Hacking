// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
class Solution {
    int areaRectangle(int P, int Q, int R, int S) {
        return (abs(P-R) * abs(Q-S));
    }
    bool firstContainsSecond(int A, int B, int C, int D, int E, int F, int G, int H) {
        bool xvalid = A<= E && E <=G && G <=C;
        bool yvalid = B<=F && F <=H && H <=D;
        return (xvalid && yvalid);
    }
    bool disJoint(int A, int B, int C, int D, int E, int F, int G, int H) {
        bool xvalid = A <= C && C <= E && E <= G;
        bool yvalid = B <= D && D <= F && F<=H;
        return (xvalid || yvalid);
    }
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        if (firstContainsSecond(A, B, C, D, E, F, G, H)) return areaRectangle(A, B, C, D);
        if (firstContainsSecond(E, F, G, H, A, B, C, D)) return areaRectangle(E, F, G, H);
        if (disJoint(A, B, C, D, E, F, G, H) || disJoint(E, F, G, H, A, B, C, D)) {
            return areaRectangle(A, B, C, D) + areaRectangle(E, F, G, H);
        }
        //find part along X that is common
        int xlen=0;
        if (A <= E) {
            xlen = (C <= G) ? C - E: G - E;
        } else {
            xlen = (C <= G) ? C - A: G - A;
        }
        //find part along Y that is common
        int ylen=0;
        if (B <= F) {
            ylen = (D <= H) ? D - F: H - F;
        } else {
            ylen = (D <= H) ? D - B: H - B;
        }
        int common = abs((ylen) * (xlen));
        return (areaRectangle(A, B, C, D) + areaRectangle(E, F, G, H) - common);
    }
};
