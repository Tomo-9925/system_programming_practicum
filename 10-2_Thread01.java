
import java.lang.*;

class Thread01 extends Thread {
    static final int N=10000000;
    static final double PI=3.1415926535;
    int Number, mytid, threads;
    double[] ret;

    public Thread01(){
	;
    }

    public Thread01(int n, int tid, int thrs, double[] x){
	Number = n;
	mytid = tid;
	threads = thrs;
	ret = x;
    }
 
    public void run(){
	int i, offset, range;
	double y;

	range = Number/threads;
	offset = range*mytid;

	y = 0.0;
	for(i=0;i<range;i++){
	    y = y + Math.sin(2.0*PI*(i+offset)/Number);
	}
	ret[mytid] = y;
	System.out.println("Thread " + mytid + " = " + y);
    }

    public static void main(String[] args){
	Thread01[] t;
	int i, threads;
	double[] x;
	double y;

	if (args.length!=1){
	    System.out.println("引数を1つ指定してください．");
	    System.exit(0);
	}
	
	threads = Integer.parseInt(args[0]);
	t = new Thread01[threads];
	x = new double[threads];

	for(i=0; i<threads; i++){
	    t[i] = new Thread01(N, i, threads, x);
	    t[i].start();
	}

	try {
	    for(i=0; i<threads; i++){
		t[i].join();
	    }
	}   catch (InterruptedException ee){ }

	y = 0.0;
	for(i=0; i<threads; i++){
	    y = y + x[i];
	}
	System.out.println("Sum of sin(x) = " + y);
    }
}
