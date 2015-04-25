// Writing in Java just to remind myself how much I hate it
// how out of touch with it I am,
// and how happy I am writing Haskell and C++ ;)
import java.io.IOException;
import java.io.FileReader;
import java.io.BufferedReader;
import java.util.*;

public class LawnMower {
    public static void main (String[] args) {
        try {
            LawnMower lm = new LawnMower();
            int testnum = lm.readFile(args[0]);

            for (int i=0; i<testnum; i++) {
                lm.runLawnMower(i);

                String s = "Case #" + (i+1) + ": ";
                
                if (lm.lawn[i].compareLawns() == true) {
                    System.out.println(s + "YES");
                } else {
                    System.out.println(s + "NO");
                }
            }
        } catch (Exception e) {
            System.out.println("Unknown file input");
            System.out.println(e.getMessage());
            e.printStackTrace();
        }
    }

    public Lawn [] lawn = new Lawn[100];

    public void runLawnMower(int l) {
        int r=0, c=0;
        for (r=0, c=0; c<lawn[l].cols(); c++) {
            int max=lawn[l].getMaxSouthScan(c);
            lawn[l].mowLawn(max, r, c);
        }
        for (r=0, c=0; r<lawn[l].rows(); r++) {
            int max=lawn[l].getMaxEastScan(r);;
            lawn[l].mowLawn(max, r, c);
        }            

        lawn[l].mowCornerCells();
    }

    public int readFile (String file) throws IOException {    
        FileReader fr = new FileReader(file);
        BufferedReader ipRead = new BufferedReader(fr);

        String numTests = ipRead.readLine();
        int testn = Integer.parseInt(numTests);

        for (int i = 0; i < testn; i++) {
            String lineNM = ipRead.readLine();
            String [] nm = lineNM.split(" ");
            int n = Integer.parseInt(nm[0]);
            int m = Integer.parseInt(nm[1]);

            List<String> list = new ArrayList<String>();

            for (int l=0; l<n; l++) {
                String line = ipRead.readLine();
                list.add(line);
            }

            String [] lines = list.toArray(new String[list.size()]);
            lawn[i] = new Lawn();
            lawn[i].readLawn(n, m, lines);
        }
        return testn;
    }
}

