import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class Monkey {

    private static long step(long num) {
        num = (num ^ (num * 64)) % 16777216;
        num = (num ^ (num / 32)) % 16777216;
        num = (num ^ (num * 2048)) % 16777216;
        return num;
    }

    private static void partOne() throws IOException {
        long total = 0;
        BufferedReader reader = new BufferedReader(new FileReader("input.txt"));
        String line;
        while ((line = reader.readLine()) != null) {
            long num = Long.parseLong(line.trim());
            for (int i = 0; i < 2000; i++) {
                num = step(num);
            }
            total += num;
        }
        reader.close();
        System.out.println(total);
    }

    private static void partTwo() throws IOException {
        Map<List<Integer>, Long> seqToTotal = new HashMap<>();
        BufferedReader reader = new BufferedReader(new FileReader("input.txt"));
        String line;

        while ((line = reader.readLine()) != null) {
            long num = Long.parseLong(line.trim());
            List<Integer> buyer = new ArrayList<>();
            buyer.add((int) (num % 10));

            for (int i = 0; i < 2000; i++) {
                num = step(num);
                buyer.add((int) (num % 10));
            }

            Set<List<Integer>> seen = new HashSet<>();
            for (int i = 0; i < buyer.size() - 4; i++) {
                int a = buyer.get(i);
                int b = buyer.get(i + 1);
                int c = buyer.get(i + 2);
                int d = buyer.get(i + 3);
                int e = buyer.get(i + 4);

                List<Integer> seq = Arrays.asList(b - a, c - b, d - c, e - d);

                if (seen.contains(seq)) {
                    continue;
                }
                seen.add(seq);

                seqToTotal.merge(seq, (long) e, Long::sum);
            }
        }
        reader.close();

        long maxValue = 0;
        for (Long value : seqToTotal.values()) {
            if (value > maxValue) {
                maxValue = value;
            }
        }
        System.out.println(maxValue);
    }

    public static void main(String[] args) throws IOException {
        partOne();
        partTwo();
    }
}
