// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------

public class Lawn {
    private int tgtLawn_[][]; //this is the lawn that was read in
    private int lawn_[][];    //this is the lawn I will mow methodically
    private int rows_;
    private int cols_;
    public final int GRASS_HEIGHT = 100;

    public void readLawn(int rows, int cols, String [] vals) {
        rows_ = rows;
        cols_ = cols;
        lawn_ = new int[rows][];
        tgtLawn_ = new int[rows][];

        for (int i=0; i<rows; i++) {
            lawn_[i] = new int[cols];
            tgtLawn_[i] = new int[cols];
        }
        for (int r=0; r<rows; r++) {
            String [] rvals = vals[r].split(" ");
            for (int c=0; c<cols; c++) {
                lawn_[r][c] = GRASS_HEIGHT;
                tgtLawn_[r][c] = Integer.parseInt(rvals[c]);
            }
        }
    }

    //takes a height h, and a starting cell (x, y)
    //sets mower to height h, and cuts everything to this height
    //if existing height < h, leaves that part untouched
    public void mowLawn(int h, int x, int y) {
        assert x==0 || x == rows_ - 1 : x;
        assert y==0 || y == cols_ - 1 : x;
        if (cornerCell_(x, y)) {
            return;         //corner cells aren't mowed in this part 
        }
        if (x == 0 || x == rows_-1) {
            mowVertical_(h, x, y);
        }
        if (y == 0 || y == cols_-1) {
            mowHorizontal_(h, x, y);
        }
    }

    public void mowCornerCells() {
        int x, y;

        //comparison for (0, 0)
        x=0;       y=0;
        int maxS1 = getMaxSouthScan(y); 
        int maxE1 = getMaxEastScan(x);
        mowVertical_(maxS1, x, y);
        mowHorizontal_(maxE1, x, y);

        //comparison for (0, cols_-1)
        x=0;       y=cols_-1;
        int maxS2 = getMaxSouthScan(y); 
        int maxW2 = getMaxWestScan_(x);
        mowVertical_(maxS2, x, y);
        mowHorizontal_(maxW2, x, y);
        
        //comparison for (rows_-1, 0)
        x=rows_-1; y=0;
        int maxN3 = getMaxNorthScan_(y);
        int maxE3 = getMaxEastScan(x);
        mowVertical_(maxN3, x, y);
        mowHorizontal_(maxE3, x, y);

        //comparison for (rows_-1, cols_-1)
        x=rows_-1; y=cols_-1;
        int maxN4 = getMaxNorthScan_(y);
        int maxW4 = getMaxWestScan_(x);
        mowVertical_(maxN4, x, y);
        mowHorizontal_(maxW4, x, y);
        
    }

    //returns true if mowed lawn equals target lawn
    public boolean compareLawns() {
        for (int r=0; r<rows_; r++) {
            for (int c=0; c<cols_; c++) {
                if (lawn_[r][c] != tgtLawn_[r][c]) {
                    return false;
                }
            }
        }

        return true;
    }

    public int getTgtCell(int r, int c) {
        return tgtLawn_[r][c];
    }

    public int cols() {
        return cols_;
    }

    public int rows() {
        return rows_;
    }

    public int getMaxSouthScan(int c) {
        int max=0;
        for (int r=0; r<rows_; r++) {   //scan southwards
            if (tgtLawn_[r][c] > max) {
                max = tgtLawn_[r][c];
            }
        }
        return max;
    }

    public int getMaxEastScan(int r) {
        int max=0;
        for (int c=0; c<cols_; c++) {   //scan eastwards
            if (tgtLawn_[r][c] > max) {
                max = tgtLawn_[r][c];
            }
        }
        return max;
    }

    private int getMaxNorthScan_(int c) {
        int max=0;
        for (int r=rows_-1; r>=0; r--) { //scan northwards
            if (tgtLawn_[r][c] > max) {
                max = tgtLawn_[r][c];
            }
        }
        return max;
    }

    private int getMaxWestScan_(int r) {
        int max=0;
        for (int c=cols_-1; c>=0; c--) { //scan westwards
            if (tgtLawn_[r][c] > max) {
                max = tgtLawn_[r][c];
            }
        }
        return max;
    }

    private void mowVertical_ (int h, int x, int y) {
        for (x=0; x<rows_; x++) {
            if (lawn_[x][y] > h) lawn_[x][y] = h;
        }
    }

    private void mowHorizontal_ (int h, int x, int y) {
        for (y=0; y<cols_; y++) {
            if (lawn_[x][y] > h) lawn_[x][y] = h;
        }
    }

    private boolean cornerCell_(int x, int y) {
        if ((x == 0 && y == 0) || (x == 0 && y == cols_-1) ||
            (x == rows_-1 && y==0) || (x==rows_-1 && y==cols_-1)) {
            return true;
        }
        return false;
    }
}
