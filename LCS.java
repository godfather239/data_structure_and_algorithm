package org.example;

/**
 * 最长公共子序列
 * 分析：
 * 令X = [X1, X2, ... Xm], Y = [Y1, Y2, ... Yn]
 * 令C[m,n]表示长度分别为m和n的两个序列的最长公共子序列的长度
 * 假设Z = [Z1, Z2, ... Zk]为1个最优解，有
 * 若m == 0或n == 0，则C[m,n] = 0
 * 若Xm == Zk, 且Xm == Yn，则C[m,n] = C[m-1,n-1] + 1
 * 若Xm == Zk, 且Xm != Yn，则C[m,n] = C[m,n-1]
 * 若Yn == Zk, 且Xm != Yn, 则C[m,n] = C[m-1,n]
 *
 * Author: greenday
 * Date:  2023/5/21
 */
public class LCS {
    private char[] x;
    private char[] y;

    public LCS(char[] x, char[] y) {
        this.x = new char[x.length+1];
        System.arraycopy(x, 0, this.x, 1, x.length);
        this.y = new char[y.length+1];
        System.arraycopy(y, 0, this.y, 1, y.length);
    }

    /**
     * 递归解，返回找到的最长公共子序列的长度，如果要输出序列，由于递归中涉及大量的字符串操作，势必会存在性能问题，因此此处只返回LCS的长度
     * @return
     */
    public int lcsRecursively() {
        return lcsRecurs_(x.length-1, y.length-1);
    }

    /**
     * 动态规划解，返回最优LCS序列
     * @return
     */
    public String lcsDP() {
        // 可直接参考背包问题的解法，用C[m][n]来存储LCS长度，
        // 用S[m][n]来存储对应C[m][n]时，最优解的构成，用3重不同的字符表示，
        //   \表示向左上方寻找，且Xm被选中，即C[m,n] = C[m-1,n-1] + 1
        //   -表示向左列寻找，即C[m,n] = C[m,n-1]
        //   |表示向上行寻找，即C[m,n] = C[m-1,n]
        // 只有表格中\对应的元素，才为LCS中的元素
        // 最后，依据这两个数组来输出最优解
        int[][] C = new int[x.length][y.length];
        char[][] S = new char[x.length][y.length];
        lcsDP_(C, S);
        int lcsLen = C[x.length-1][y.length-1];
        if (lcsLen == 0) {
            return null;
        }
        int n = x.length-1;
        int m = y.length-1;
        StringBuilder builder = new StringBuilder();
        lcsDPPrint_(n, m, S, builder);
        return builder.toString();
    }

    public void lcsDPPrint_(int n, int m, char[][] S, StringBuilder builder) {
        if (n == 0 || m == 0) {
            return;
        }
        if (S[n][m] == '\\') {
            lcsDPPrint_(n-1, m-1, S, builder);
            builder.append(x[n]);
        } else if (S[n][m] == '-') {
            lcsDPPrint_(n, m-1, S, builder);
        } else {
            lcsDPPrint_(n-1, m, S, builder);
        }
//        if (S[n][m] == 1) {
//            builder.append(x[n]);
//            lcsDPPrint_(n-1, m-1, C, S, builder);
//        } else {
//            if (S[n-1][m] == 1) {
//                lcsDPPrint_(n-1, m, C, S, builder);
//            } else {
//                lcsDPPrint_(n, m-1, C, S, builder);
//            }
//        }
    }

    private void lcsDP_(int[][] C, char[][] S) {
        // 初始化表格
        // 初始化边界值
        for (int i = 0; i < x.length; ++i) {
            C[i][0] = 0;
        }
        for (int j = 0; j < y.length; ++j) {
            C[0][j] = 0;
        }
        // 自底向上构建表格
        for (int i = 1; i < x.length; ++i) {
            for (int j = 1; j < y.length; ++j) {
                if (x[i] == y[j]) {
                    C[i][j] = C[i-1][j-1] + 1;
                    S[i][j] = '\\';
                } else {
                    if (C[i-1][j] >= C[i][j-1]) {
                        C[i][j] = C[i-1][j];
                        S[i][j] = '|';
                    } else {
                        C[i][j] = C[i][j-1];
                        S[i][j] = '-';
                    }
                }
            }
        }
    }

    private int lcsRecurs_(int m, int n) {
        if (m == 0 || n == 0) {
            return 0;
        }
        if (x[m] == y[n]) {
            return lcsRecurs_(m-1, n-1) + 1;
        }
        return Math.max(lcsRecurs_(m, n-1), lcsRecurs_(m-1, n));
    }

    public static void main(String[] args) {
        char[] x = new char[] {'A', 'C', 'B', 'D', 'B'};
        char[] y = new char[] {'A', 'B', 'E', 'D', 'F', 'B'};
        // 预期LCS == 4
        LCS lcs = new LCS(x, y);
        System.out.println("LCS = " + lcs.lcsRecursively());
        System.out.println("by DP, LCS = " + lcs.lcsDP());
    }
}
