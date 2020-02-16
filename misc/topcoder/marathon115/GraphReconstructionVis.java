import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import java.security.*;
import java.util.*;
import java.net.URL;
import javax.swing.*;
import javax.imageio.*;


public class GraphReconstructionVis {

    //finals 
    //test parameters
    private static int minN = 10, maxN = 100;
    private static int minK = 1, maxK = 10;
    private static int Inf = 1000000;
    
    //inputs
    int N;         //number of nodes
    double C;      //connectivity
    int K;         //number of appearances of each node
    boolean[][] AdjMat;     //adjacency matrix of real graph
    java.util.List<String> Paths;
        
    //outputs
    double Score;  
    int TP;         //number of green edges
    int FP;         //number of red edges
    int FN;         //number of true edges we missed
    int TN;         //number of non-edges we missed correctly    
    double Precision;
    double Recall;
    String[] Solution;     
    boolean[][] AdjPredicted;
    
    // -----------------------------------------
    void generate(String seedStr) {
      try {
        // generate test case
        SecureRandom r1 = SecureRandom.getInstance("SHA1PRNG"); 
        long seed = Long.parseLong(seedStr);
        r1.setSeed(seed);
  
        //generate number of nodes
        N = r1.nextInt(maxN - minN + 1) + minN;
        
        //set easiest/hardest seeds
        if (seed == 1) N = minN;
        if (seed == 2) N = maxN;      
        
        //generate connectivity value C
        C = r1.nextDouble()*(2.0/N) + 1.0/N;             

        //generate K parameter
        K = r1.nextInt(maxK - minK + 1) + minK;    
        if (seed == 1) K = 2;
        if (seed == 2) K = minK;


        //generate the true adjacency matrix
        AdjMat = new boolean[N][N];

        for (int i=0; i<N; i++)
          for (int k=i+1; k<N; k++)
            if (r1.nextDouble() < C)
            {
              AdjMat[i][k]=true;
              AdjMat[k][i]=true;
            }        

        //compute shortest paths between every pair of nodes
        int[][] shortestPath=new int[N][N];
        for (int i=0; i<N; i++)
        {
          shortestPath[i][i]=0;
          for (int k=i+1; k<N; k++)
          {
            if (AdjMat[i][k]) shortestPath[i][k]=1;
            else  shortestPath[i][k]=Inf;

            shortestPath[k][i]=shortestPath[i][k];      //make symmetric
          }
        }

        //run all-pairs shortest path. Best algorithm ever!
        for (int k=0; k<N; k++)
          for (int i=0; i<N; i++)
            for (int j=0; j<N; j++)
              shortestPath[i][j]=Math.min(shortestPath[i][j],shortestPath[i][k]+shortestPath[k][j]);        
              
        //convert Inf to -1
        for (int i=0; i<N; i++)
          for (int k=0; k<N; k++)
            if (shortestPath[i][k]==Inf)
              shortestPath[i][k]=-1;

        //generate paths through the graph
        int[] seen=new int[N];
        boolean[][] seen2=new boolean[N][N];
        int countSeen=0;
        Paths = new ArrayList<String>();

        int[] ind=new int[N*N];
        for (int i=0; i<ind.length; i++) ind[i]=i;
        shuffle(r1,ind);

        for (int i=0; i<ind.length; i++)
        {
          int node1=ind[i]/N;
          int node2=ind[i]%N;
          if (node1>=node2) continue;           //out of order
          if (seen2[node1][node2]) continue;    //already seen this pair

          seen[node1]++;
          if (seen[node1]==K) countSeen++;
          seen[node2]++;
          if (seen[node2]==K) countSeen++;
          seen2[node1][node2]=true;     
          seen2[node2][node1]=true;
          Paths.add(node1+" "+node2+" "+shortestPath[node1][node2]);

          if (countSeen==N) break;      //seen all nodes at least K times         
        }        
              
        if (Debug) printTest(seedStr);        
      }
      catch (Exception e) {
        addFatalError("An exception occurred while generating test case.");
        e.printStackTrace(); 
      }
    }

    //shuffle the array randomly
    void shuffle(SecureRandom r1, int[] a)
    {
      for (int i=0; i<a.length; i++)
      {
        int k=(int)(r1.nextDouble()*(a.length-i)+i);
        int temp=a[i];  
        a[i]=a[k];
        a[k]=temp;  
      }   
    }      
    
    void printTest(String seed)
    {
        System.err.println("seed = "+seed);
        System.err.println("Number of nodes, N = "+N);
        System.err.println("Connectivity, C = "+C);
        System.err.println("Appearances for each node, K = "+K);
        System.err.println("True graph adjacency:");      
        for (int i=0; i<N; i++)
        {
          for (int k=0; k<N; k++) 
            System.err.print(AdjMat[i][k] ? '1' : '0');
          System.err.println();
        }
        System.err.println("Paths:");
        for (String s : Paths) System.err.println(s);
    }
            
        
    // -----------------------------------------
    public double runTest(String seed) {
      try {
        generate(seed);        

        AdjPredicted=new boolean[N][N];

        if (proc != null) {
          // call the solution
          try { 
              Solution = callSolution();
          } catch (Exception e) {
              addFatalError("Failed to get result from your solution.");
              return -1.0;
          }

          // check the return and score it
          if (Solution == null) {
              addFatalError("Your return contained an invalid number of elements.");
              return -1.0;
          }
          if (Solution.length != N) {
              addFatalError("Your return did not contain "+N+" strings.");
              return -1.0;
          }
          
          for (int i=0; i<N; i++)
          {
            if (Solution[i].length() != N)
            {
              addFatalError("Row "+i+" does not contain "+N+" characters.");
              return -1.0;              
            }
            for (int k=0; k<N; k++)
            {
              char c=Solution[i].charAt(k);
              if (!(c=='0' || c=='1')) 
              {
                addFatalError("Row "+i+" column "+k+" has illegal character.");
                return -1.0;                              
              }
              AdjPredicted[i][k]=(c=='1');
            }
          }
          
          for (int i=0; i<N; i++)
            for (int k=i; k<N; k++)
              if (AdjPredicted[i][k]!=AdjPredicted[k][i])
              {
                addFatalError("Row "+i+" column "+k+" does not match row "+k+" column "+i);
                return -1.0;                                            
              }


          if (Debug)
          {
            System.err.println("\nPredicted graph adjacency:");
            for (int i=0; i<N; i++)
            {
              for (int k=0; k<N; k++) System.err.print(AdjPredicted[i][k] ? "1" : "0");
              System.err.println();
            }
          }
            
            
          //compute the raw score 
          TP=0;         //number of green edges
          FP=0;         //number of red edges
          FN=0;         //number of true edges we missed
          TN=0;         //number of non-edges we missed correctly
    
          for (int r=0; r<N; r++)
            for (int c=r+1; c<N; c++)
            {
              if (AdjPredicted[r][c])
              {
                if (AdjMat[r][c]) TP++;
                else FP++;
              }
              else
              {
                if (AdjMat[r][c]) FN++;
                else TN++;
              }
            }

          Precision = (TP+FP==0 ? 0 : TP*1.0/(TP+FP));
          Recall = (TP+FN==0 ? 0 : TP*1.0/(TP+FN));
          //compute the F1 score
          Score = (Precision + Recall < 1e-9 ? 0 : (2 * Precision * Recall)/(Precision + Recall));

          if (Debug)
          {
            System.err.println("TP "+TP);
            System.err.println("FP "+FP);
            System.err.println("FN "+FN);
            System.err.println("TN "+TN);
            System.err.println("Precision "+Precision);
            System.err.println("Recall "+Recall);
          }
                                      
          
          if (vis) {
            //show seed in the title. Thank you wleite for the idea!
            jf.setTitle("GraphReconstruction, seed = " + seed);
            jf.setVisible(true);         

            int extraW=300;
            int extraH=20;
            boolean fullScreen=false;

            if (fullScreen)
            {        
              Insets frameInsets = jf.getInsets();
              int fw = frameInsets.left + frameInsets.right;
              int fh = frameInsets.top + frameInsets.bottom;
              Toolkit toolkit = Toolkit.getDefaultToolkit();
              Dimension screenSize = toolkit.getScreenSize();
              Insets screenInsets = toolkit.getScreenInsets(jf.getGraphicsConfiguration());
              screenSize.width -= screenInsets.left + screenInsets.right;
              screenSize.height -= screenInsets.top + screenInsets.bottom;
              int size = Math.min(screenSize.width - fw - extraW, screenSize.height - fh - extraH);
              width=size;
              height=size-50;            
              jf.setSize(size + fw + extraW, size + fh + extraH);              
              draw();
            }
            else
            {
              Insets frameInsets = jf.getInsets();
              int fw = frameInsets.left + frameInsets.right;
              int fh = frameInsets.top + frameInsets.bottom;
              jf.setSize(width + extraW + fw, height + extraH + fh + 50);        
            }

          }   
        }
       
        return Score;
      }
      catch (Exception e) { 
        addFatalError("An exception occurred while trying to get your program's results.");
        e.printStackTrace(); 
        return -1.0;
      }
    }       
       
    
// ------------- visualization part ------------
    JFrame jf;
    Vis v;
    static String exec;
    static boolean vis;
    static Process proc;
    InputStream is;
    OutputStream os;
    BufferedReader br;
    static int height=900;
    static int width=1200;
    static boolean Debug;

    
    // -----------------------------------------
    private String[] callSolution() throws IOException, NumberFormatException {
        if (exec == null) return null;

        String s=N+"\n"+C+"\n"+K+"\n"+Paths.size()+"\n";
        os.write(s.getBytes());
        for (String a : Paths)
        {
          s=a+"\n";
          os.write(s.getBytes());
        }
        os.flush();

        // and get the return value
        String[] out=new String[Integer.parseInt(br.readLine())];
        for (int i = 0; i < out.length; i++) out[i] = br.readLine();
        return out;
    }
    // -----------------------------------------
    void draw() {
        if (!vis) return;
        v.repaint();
    }
    
    
    int[] getNode(double angle, int i, double radius, double centerX, double centerY)
    {
      int x=(int)Math.round(Math.cos(angle*i)*radius+centerX);
      int y=(int)Math.round(Math.sin(angle*i)*radius+centerY);
      return new int[]{x,y};
    }
    
    // -----------------------------------------
    public class Vis extends JPanel implements MouseListener, WindowListener {
        public void paint(Graphics g) {
        
          //Use antialiasing when painting. Thank you wleite for the idea!
          ((Graphics2D) g).setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
          ((Graphics2D) g).setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);
          ((Graphics2D) g).setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
                               
          int startX=20;
          int startY=20;
          int gap=50;
          int nodeRadius=5;

          double radius=Math.min((height-startY)/2.0,(width-gap-startX)/4.0);
          double centerX=(width-gap-startX)/4.0+startX;
          double centerY=(height-startY)/2.0+startY;
          double centerX2=startX+(width-gap-startX)/4.0*3+gap;
          double angle=2*Math.PI/N;
                    
          // gray background
          g.setColor(new Color(0xDDDDDD));
          g.fillRect(0,0,10000,10000);
          // white rectangle
          g.setColor(Color.WHITE);
          g.fillRect(startX,startY,width,height);
          
          //true graph
          //points
          for (int i=0; i<N; i++) 
          {
            g.setColor(Color.BLACK);
            int[] node=getNode(angle, i, radius, centerX, centerY);
            g.fillOval(node[0]-nodeRadius/2,node[1]-nodeRadius/2,nodeRadius,nodeRadius);
          }
          //edges
          for (int i=0; i<N; i++)
          {
            int[] node1=getNode(angle, i, radius, centerX, centerY);
            for (int k=i+1; k<N; k++)
              if (AdjMat[i][k])
              {
                g.setColor(Color.BLACK);                
                int[] node2=getNode(angle, k, radius, centerX, centerY);
                g.drawLine(node1[0],node1[1],node2[0],node2[1]);
              }
          }
          

          //predicted graph
          //points
          for (int i=0; i<N; i++) 
          {
            g.setColor(Color.BLACK);
            int[] node=getNode(angle, i, radius, centerX2, centerY);
            g.fillOval(node[0]-nodeRadius/2,node[1]-nodeRadius/2,nodeRadius,nodeRadius);
          }    
          //edges
          for (int i=0; i<N; i++)
          {
            int[] node1=getNode(angle, i, radius, centerX2, centerY);
            for (int k=i+1; k<N; k++)
            {
              if (AdjPredicted[i][k]==AdjMat[i][k]) g.setColor(Color.GREEN);                
              else g.setColor(Color.RED);
              
              if (AdjPredicted[i][k])
              {
                int[] node2=getNode(angle, k, radius, centerX2, centerY);
                g.drawLine(node1[0],node1[1],node2[0],node2[1]);
              }
            }
          }                  

                        
          //display score and info
          g.setColor(Color.BLACK);                    
          g.setFont(new Font("Arial",Font.BOLD,18));                                                
          g.drawString("SCORE = "+String.format("%.5f", Score),width+startX+30,60);            
          g.drawString("N = "+N,width+startX+30,110);  
          g.drawString("C = "+String.format("%.5f", C),width+startX+30,130);  
          g.drawString("K = "+K,width+startX+30,150);  
          g.drawString("TP = "+TP,width+startX+30,200);  
          g.drawString("FP = "+FP,width+startX+30,220);  
          g.drawString("FN = "+FN,width+startX+30,240);  
          g.drawString("TN = "+TN,width+startX+30,260);  
          g.drawString("Precision = "+String.format("%.5f", Precision),width+startX+30,280);  
          g.drawString("Recall = "+String.format("%.5f", Recall),width+startX+30,300);            

          g.drawString("True Graph",(int)(centerX)-50,60);            
          g.drawString("Predicted Graph",(int)(centerX2)-75,60);            
        }
    
        
        // -------------------------------------
        public Vis()
        {
            jf.addWindowListener(this);             
        }
        // -------------------------------------
        //WindowListener
        public void windowClosing(WindowEvent e){ 
            if(proc != null)
                try { proc.destroy(); } 
                catch (Exception ex) { ex.printStackTrace(); }
            System.exit(0); 
        }
        public void windowActivated(WindowEvent e) { }
        public void windowDeactivated(WindowEvent e) { }
        public void windowOpened(WindowEvent e) { }
        public void windowClosed(WindowEvent e) { }
        public void windowIconified(WindowEvent e) { }
        public void windowDeiconified(WindowEvent e) { }
        // -------------------------------------
        //MouseListener
        public void mouseClicked(MouseEvent e) { }
        public void mousePressed(MouseEvent e) { }
        public void mouseReleased(MouseEvent e) { }
        public void mouseEntered(MouseEvent e) { }
        public void mouseExited(MouseEvent e) { }
    }
    // -----------------------------------------
    public GraphReconstructionVis(String seed) {
      try {
        if (vis)
        {
            jf = new JFrame();            
            v = new Vis();
            jf.getContentPane().add(v);
        }
        if (exec != null) {
            try {
                Runtime rt = Runtime.getRuntime();
                proc = rt.exec(exec);
                os = proc.getOutputStream();
                is = proc.getInputStream();
                br = new BufferedReader(new InputStreamReader(is));
                new ErrorReader(proc.getErrorStream()).start();
            } catch (Exception e) { e.printStackTrace(); }
        }
        System.out.println("Score = " + runTest(seed));
        if (proc != null)
            try { proc.destroy(); } 
            catch (Exception e) { e.printStackTrace(); }
      }
      catch (Exception e) { e.printStackTrace(); }
    }
       
    
    // -----------------------------------------
    public static void main(String[] args) {
        String seed = "1";
        vis = true;
        Debug = false;
        for (int i = 0; i<args.length; i++)
        {   if (args[i].equals("-seed"))
                seed = args[++i];
            if (args[i].equals("-exec"))
                exec = args[++i];
            if (args[i].equals("-novis"))
                vis = false;
            if (args[i].equals("-debug"))
                Debug = true;
        }
            
        GraphReconstructionVis f = new GraphReconstructionVis(seed);
    }
    // -----------------------------------------
    void addFatalError(String message) {
        System.out.println(message);
    }
}

class ErrorReader extends Thread{
    InputStream error;
    public ErrorReader(InputStream is) {
        error = is;
    }
    public void run() {
        try {
            byte[] ch = new byte[50000];
            int read;
            while ((read = error.read(ch)) > 0)
            {   String s = new String(ch,0,read);
                System.out.print(s);
                System.out.flush();
            }
        } catch(Exception e) { }
    }
}
