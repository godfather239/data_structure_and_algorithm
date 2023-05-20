package org.example;

import java.util.Arrays;
import java.util.Random;

/**
 * 0-1背包问题
 * 有N个物品，每个物品的重量为Wi，价值为Vi，背包最大容量为W，求背包能够放入的所有物品的最大总价值，并输出物品组合
 * 思路：
 * 一般而言，令P(i, Y)为总重量不超过Y情况下，前i个商品的总价值，则有：
 *   P(0, Y) = 0
 *   若Wi > Y，P(i,Y) = P(i-1,Y)
 *   若Wi <= Y, P(i,Y) = Max{P(i-1,Y), P(i-1, Y-Wi) + Vi}
 *
 * 非递归解：
 * 构造N*W的矩阵，自底向上填充矩阵元素，P[i][y]表示总重量不超过y的情况下，前i个商品的最大价值，注意是前i个，而不是N个里任选i个
 * 在构造一个N*W的矩阵，用于存储P[i][y]对应的第i个商品的选择情况，为1表示选择，为0表示不选择
 * 输出最优解：即输出P[N][W]
 * 输出最优解对应的商品组合：
 * 自顶向下，依次查找：S[N][W]，如果当前S为1，则下一轮查找S[N-1][W-w[N]]；否则，下一轮查找S[N-1][W]
 *
 * Author: greenday
 * Date:  2023/5/20
 */
public class Knapsack {

    // 重量数组
    private int[] w;
    // 价值数组
    private int[] p;
    // 背包容量
    private int W;
    // 商品总数
    private int N;

    // 总价值最优解矩阵，P[i][y]
    private int[][] sum;

    // 对应最优解时商品i是否选中
    private int[][] sel;

    public Knapsack(int[] w, int[] p, int n, int W) {
        this.w = w;
        this.p = p;
        this.N = n;
        this.W = W;
        this.sum = new int[N+1][W+1];
        this.sel = new int[N+1][W+1];
    }

    /**
     * 空间复杂度O(N+W)，时间复杂度O(2^N)，且栈溢出风险高，不能输出最优解对应的商品组合
     * @return
     */
    public int getOptimalByRecursive() {
        /**
         * 为什么数组从后往前遍历可以work？
         * 因为内部逻辑的取max部分其实就是0-1选择，逻辑上，相对于对当前商品赋0或者赋1，最终，所有商品都会赋上1个值，得到1个长为N的01序列
         * 而这个序列，就实际表示了商品组合的最优解
         */
        return optimal_recursive(N-1, W);
    }

    public int[] getOptimalByDP() {
        optimal_dp();
        int[] res = new int[N+1];
        res[0] = sum[N][W];
        int i = N;
        int y = W;
        while (i > 0 && y > 0) {
            if (sel[i][y] > 0) {
                res[i] = p[i-1];
                y = y - w[i-1];
            } else {
                res[i] = 0;
            }
            --i;
        }
        return res;
    }

    /**
     * 动态规划实现，空间复杂度O(N*W)，时间复杂度O(N*W)
     * 空间复杂度可以通过滚动数组进行优化，将复杂度由O(N*W)降为O(2*W)，其中一行表示商品i被选中，另一行表示商品i未被选中
     */
    private void optimal_dp() {
        // 初始化P[0,y]
        for (int i = 0; i < W+1; ++i) {
            sum[0][i] = 0;
            sel[0][i] = 0;
        }
        // 初始化P[i,0]
        for (int i = 0; i < N+1; ++i) {
            sum[i][0] = 0;
            sel[i][0] = 0;
        }
        // 循环商品总数
        for (int i = 1; i <= N; ++i) {
            // 循环背包容量
            for (int y = 1; y <= W; ++y) {
                if (w[i-1] > y) {
                    // 未选择商品i
                    sum[i][y] = sum[i-1][y];
                    sel[i][y] = 0;
                } else {
                    int sumWithI = p[i-1] + sum[i-1][y-w[i-1]];
                    if (sumWithI > sum[i-1][y]) {
                        // 选择商品i
                        sum[i][y] = sumWithI;
                        sel[i][y] = 1;
                    } else {
                        // 未选择商品i
                        sum[i][y] = sum[i-1][y];
                        sel[i][y] = 0;
                    }
                }
            }
        }
    }

    /**
     * 递归实现
     * 返回前i个商品在总重量小于等于y的约束下的最大价值
     * @param i i从0开始，表示第一个商品
     * @param y
     * @return
     */
    private int optimal_recursive(int i, int y) {
        if (i < 0 || y <= 0) {
            return 0;
        }
        if (w[i] > y) {
            return optimal_recursive(i-1, y);
        }
        int a = optimal_recursive(i-1, y);
        int b = optimal_recursive(i-1, y-w[i]) + p[i];
        if (b > a) {
            return b;
        } else {
            return a;
        }
    }

    public static void main(String[] args) {
        int n = 5;
        Random random = new Random();
        int[] w = new int[]{94, 27, 32, 56, 67};
        int[] p = new int[]{4, 5, 9, 3, 4};
//        int[] w = new int[]{94, 27, 32, 56, 67, 79, 72, 25, 74, 37};
//        int[] p = new int[]{4, 0, 9, 3, 4, 9, 5, 9, 3, 7};
//        for (int i = 0; i < n; ++i) {
//            w[i] = random.nextInt(100);
//            p[i] = random.nextInt(10);
//        }
        int[] quotas = new int[]{20, 50, 100, 150, 200};
        System.out.println("weight array: " + Arrays.toString(w));
        System.out.println("value array: " + Arrays.toString(p));
        // 递归测试
        for (int i = 0; i < 5; ++i) {
            Knapsack knapsack = new Knapsack(w, p, n, quotas[i]);
            System.out.println("weight quota: " + quotas[i]);
            System.out.println("max total value: " + knapsack.getOptimalByRecursive());
        }
        // DP测试
        for (int i = 0; i < 5; ++i) {
            Knapsack knapsack = new Knapsack(w, p, n, quotas[i]);
            System.out.println("weight quota: " + quotas[i]);
            int[] res = knapsack.getOptimalByDP();
            System.out.println("max total value: " + Arrays.toString(res));
        }
    }
}
