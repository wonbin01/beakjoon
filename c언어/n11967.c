#include <stdio.h>
#include <stdlib.h>

int direction[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};  // ��, ��, ��, ��

typedef struct Element {
    int r;
    int c;
    struct Element *next;
} Element;

void bfs(int n, int **turn, Element **light, int *count, int **visited);

int main(void) {
    int n, m;
    int count = 1;  // (0, 0)���� �̹� ���� ���� ����
    scanf("%d %d", &n, &m);  // n�� �갣�� ũ��, m�� �� �� �Է¹��� ����
    int x, y, a, b;  // (x, y) �濡�� (a, b) ���� ���� ų �� ����

    Element **light = (Element **)malloc(n * sizeof(Element *));  // ���� ���� �ִ� ���� ��Ÿ��
    for (int i = 0; i < n; i++) {
        light[i] = (Element *)malloc(n * sizeof(Element));
        for (int j = 0; j < n; j++) {
            light[i][j].r = i;
            light[i][j].c = j;
            light[i][j].next = NULL;
        }
    }

    // �Է¹޾Ƽ� ���� �� �� �ִ� �� ����
    for (int t = 0; t < m; t++) {
        scanf(" %d %d %d %d", &x, &y, &a, &b);
        x = x - 1;
        y = y - 1;
        a = a - 1;
        b = b - 1;

        Element *newedge = (Element *)malloc(sizeof(Element));
        newedge->r = a;
        newedge->c = b;
        newedge->next = NULL;

        // ���� ����Ʈ�� �� �߰�
        if (light[x][y].next == NULL) {
            light[x][y].next = newedge;
        } else {
            Element *current = light[x][y].next;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newedge;
        }
    }

    // �湮 ó���� ���� ���� �ִ� �� �ʱ�ȭ
    int **visited = (int **)malloc(n * sizeof(int *));  // �湮�� �� ��Ÿ���� �迭
    int **turn = (int **)malloc(n * sizeof(int *));  // �� ���� �ִ� �� ��Ÿ���� �迭
    for (int i = 0; i < n; i++) {
        visited[i] = (int *)malloc(n * sizeof(int));
        turn[i] = (int *)malloc(n * sizeof(int));
    }

    // �ʱ�ȭ
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            turn[i][j] = 0;
            visited[i][j] = 0;
        }
    }

    turn[0][0] = 1;  // (0, 0)���� ���� ���� ����
    visited[0][0] = 1;  // (0, 0) �湮 ó��
    count = 1;  // (0, 0)�� ī��Ʈ�� ����

    // �� �� BFS ����
    bfs(n, turn, light, &count, visited);

    // ���� ���� �ִ� ���� �� �ִٸ� BFS�� �ٽ� ����
    int moreLights = 1;
    while (moreLights) {
        moreLights = 0;
        // ���� �����ִ� ���� ���� �� �ٽ� BFS�� �õ�
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (turn[i][j] == 1 && visited[i][j] == 0) {
                    // ���� ���� �ְ� �湮���� �ʾҴٸ� BFS ����
                    moreLights = 1;
                    bfs(n, turn, light, &count, visited);
                    break;
                }
            }
            if (moreLights) break;
        }
    }

    printf("%d\n", count);  // ���� ų �� �ִ� ���� ���� ���

    return 0;
}

void bfs(int n, int **turn, Element **light, int *count, int **visited) {
    int queue[n * n][2];  // ť�� ���� �迭
    int front = 0;
    int rear = 0;

    queue[rear][0] = 0;  // ���� ���� (0, 0)
    queue[rear][1] = 0;
    rear++;

    // BFS Ž�� ����
    while (rear > front) {
        int cx = queue[front][0];
        int cy = queue[front][1];
        front++;

        // ���� �濡�� ���� ų �� �ִ� �� Ž��
        Element *current = light[cx][cy].next;
        while (current != NULL) {
            if (turn[current->r][current->c] == 0) {  // ���� ���� ������ ���� ��
                turn[current->r][current->c] = 1;  // ���� Ŵ
                (*count)++;  // ���� �� ���� �� ����
            }
            current = current->next;
        }

        // ����� ������ �̵�
        for (int i = 0; i < 4; i++) {
            int nx = cx + direction[i][0];
            int ny = cy + direction[i][1];

            if (nx >= 0 && nx < n && ny >= 0 && ny < n && turn[nx][ny] == 1 && visited[nx][ny] == 0) {
                visited[nx][ny] = 1;  // �湮 ó��
                queue[rear][0] = nx;
                queue[rear][1] = ny;
                rear++;
            }
        }
    }
}
