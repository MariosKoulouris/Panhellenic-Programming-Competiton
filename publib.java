/* USER: user176.36pdp
LANG: Java
TASK: publib */

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.util.*;

public class publib {
    public static void main(String[] args) {
        String inputFileName = "publib.in";
        String outputFileName = "publib.out";
        try {
            File inputFile = new File(inputFileName);
            Scanner scanner = new Scanner(inputFile);

            String[] firstLine = scanner.nextLine().split(" ");
            int N = Integer.parseInt(firstLine[0]);
            int M = Integer.parseInt(firstLine[1]);

            List<List<Integer>> graph = new ArrayList<>();
            for (int i = 0; i <= N; i++) {
                graph.add(new ArrayList<Integer>());
            }

            for (int i = 0; i < M; i++) {
                int u = scanner.nextInt();
                int v = scanner.nextInt();
                graph.get(u).add(v);
                graph.get(v).add(u);
            }
            scanner.close();
            int minDistance = Integer.MAX_VALUE;


            for (int village = 1; village <= N; village++) {
                boolean[] visited = new boolean[N + 1];
                Queue<Integer> queue = new LinkedList<>();
                queue.offer(village);
                visited[village] = true;
                int distance = -1;
                while (!queue.isEmpty()) {
                    int size = queue.size();
                    for (int i = 0; i < size; i++) {
                        int currentVillage = queue.poll();
                        for (int neighbor : graph.get(currentVillage)) {
                            if (!visited[neighbor]) {
                                queue.offer(neighbor);
                                visited[neighbor] = true;
                            }
                        }
                    }
                    distance++;
                }
                minDistance = Math.min(minDistance, distance);

            }
            PrintWriter writer = new PrintWriter(new FileOutputStream(outputFileName));
            writer.print(minDistance); 
            writer.close();
        } catch (FileNotFoundException e) {
            System.out.println("File not found: " + e.getMessage());
        }

    }
}