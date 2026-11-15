//practical 3
import heapq

# Graph representing cities and distances
graph = {
    'A': {'B': 4, 'C': 3},
    'B': {'D': 5, 'E': 2},
    'C': {'F': 7},
    'D': {'G': 3},
    'E': {'G': 5},
    'F': {'G': 2},
    'G': {}
}

# Estimated distance to destination G
h = {
    'A': 7,
    'B': 5,
    'C': 6,
    'D': 3,
    'E': 4,
    'F': 2,
    'G': 0
}

# Greedy Best First Search
def greedy(start, goal):
    pq = [(h[start], start, [start])]
    visited = set()

    while pq:
        _, node, path = heapq.heappop(pq)

        if node == goal:
            return path

        if node not in visited:
            visited.add(node)

            for neighbour in graph[node]:
                if neighbour not in visited:
                    heapq.heappush(
                        pq, (h[neighbour], neighbour,
                             path + [neighbour])
                    )

    return None


# A* Search
def astar(start, goal):
    pq = [(h[start], 0, start, [start])]
    visited = set()

    while pq:
        f, cost, node, path = heapq.heappop(pq)

        if node == goal:
            return path, cost

        if node not in visited:
            visited.add(node)

            for neighbour, distance in graph[node].items():
                new_cost = cost + distance

                heapq.heappush(
                    pq,
                    (new_cost + h[neighbour],
                     new_cost,
                     neighbour,
                     path + [neighbour])
                )

    return None, float('inf')


start = 'A'
goal = 'G'

print("Greedy Best First Search:")
print(greedy(start, goal))

print("\nA* Search:")
path, cost = astar(start, goal)
print("Path:", path)
print("Total Cost:", cost)


//PR 5 
    import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split

# 1. Load your local CSV dataset
df = pd.read_csv("your_dataset.csv")

//basic

//PR 5 

pip install pandas numpy matplotlib seaborn scikit-learn


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split

# 1. Load Titanic dataset
df = sns.load_dataset('titanic')

print("First five records:")
print(df.head())

# 2. Check dataset information
print("\nDataset Information:")
print(df.info())

# 3. Check missing values
print("\nMissing Values:")
print(df.isnull().sum())

# 4. Remove duplicate records
df = df.drop_duplicates()

# 5. Select useful columns
df = df[['survived', 'pclass', 'sex',
         'age', 'fare', 'embarked']].copy()

# 6. Handle missing values
df['age'] = df['age'].fillna(df['age'].median())
df['fare'] = df['fare'].fillna(df['fare'].median())
df['embarked'] = df['embarked'].fillna(
    df['embarked'].mode()[0]
)

# 7. Encoding categorical values
df = pd.get_dummies(df, columns=['sex', 'embarked'],
                    drop_first=True, dtype=int)

print("\nAfter Encoding:")
print(df.head())

# 8. Statistical analysis
print("\nStatistical Analysis:")
print(df.describe())

# 9. Feature scaling
scaler = StandardScaler()

df[['age', 'fare']] = scaler.fit_transform(
    df[['age', 'fare']]
)

print("\nAfter Feature Scaling:")
print(df.head())

# 10. Histogram
plt.hist(df['age'], bins=20)
plt.title("Age Distribution")
plt.xlabel("Age")
plt.ylabel("Frequency")
plt.show()

# 11. Boxplot
sns.boxplot(x=df['fare'])
plt.title("Fare Boxplot")
plt.show()

# 12. Split dataset
X = df.drop('survived', axis=1)
y = df['survived']

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

print("\nTraining Data:", X_train.shape)
print("Testing Data:", X_test.shape)
print("Practical Completed Successfully!")





//PR 7 
    
import numpy as np

from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler

from sklearn.linear_model import LogisticRegression
from sklearn.neighbors import KNeighborsClassifier

from sklearn.metrics import (
    accuracy_score,
    precision_score,
    recall_score,
    f1_score,
    confusion_matrix
)

# 1. Load dataset
data = load_breast_cancer()

X = data.data
y = data.target

print("Dataset Loaded Successfully")

# 2. Split dataset
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42,
    stratify=y
)

# 3. Feature scaling
scaler = StandardScaler()

X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# 4. Create models
models = {
    "Logistic Regression": LogisticRegression(max_iter=1000),
    "KNN": KNeighborsClassifier(n_neighbors=5)
}

# 5. Train and evaluate models
for name, model in models.items():

    model.fit(X_train, y_train)

    y_pred = model.predict(X_test)

    print("\n", name)

    print("Accuracy:",
          accuracy_score(y_test, y_pred))

    print("Precision:",
          precision_score(y_test, y_pred))

    print("Recall:",
          recall_score(y_test, y_pred))

    print("F1 Score:",
          f1_score(y_test, y_pred))

    print("Confusion Matrix:")
    print(confusion_matrix(y_test, y_pred))







//PR9


import matplotlib.pyplot as plt

from sklearn.datasets import load_iris
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans, AgglomerativeClustering

from scipy.cluster.hierarchy import dendrogram, linkage

# 1. Load dataset
data = load_iris()
X = data.data

print("Dataset Loaded Successfully")
print("First five records:")
print(X[:5])

# 2. Feature scaling
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# 3. Elbow Method
wcss = []

for k in range(1, 11):
    model = KMeans(n_clusters=k, random_state=42, n_init=10)
    model.fit(X_scaled)
    wcss.append(model.inertia_)

plt.plot(range(1, 11), wcss, marker='o')
plt.title("Elbow Method")
plt.xlabel("Number of Clusters")
plt.ylabel("WCSS")
plt.show()

# 4. K-Means Clustering
kmeans = KMeans(n_clusters=3, random_state=42, n_init=10)

kmeans_labels = kmeans.fit_predict(X_scaled)

print("\nK-Means Cluster Labels:")
print(kmeans_labels)

# 5. Hierarchical Clustering
linked = linkage(X_scaled, method='ward')

plt.figure(figsize=(10, 5))
dendrogram(linked)
plt.title("Hierarchical Clustering Dendrogram")
plt.xlabel("Data Points")
plt.ylabel("Distance")
plt.show()

# 6. Apply Agglomerative Clustering
hc = AgglomerativeClustering(n_clusters=3)

hc_labels = hc.fit_predict(X_scaled)

print("\nHierarchical Cluster Labels:")
print(hc_labels)

print("\nPractical Completed Successfully!")
















// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>


// int main()
// {
//     int a[20], n, i, j, temp;
//     pid_t pid;

//     printf("Enter number of elements: ");
//     scanf("%d", &n);

//     printf("Enter elements: ");
//     for(i = 0; i<n; i++)
//         {
//             scanf("%d", &a[i]);
            
//         }
//     pid = fork();

//     if(pid == 0){

//         printf("\nChild process sorting in ascending order: \n");

//         for(i=0; i<n; i++){
//             for(j=0; j<n-i-1; j++){

//                 if(a[j] > a[j+1])
//                 {
//                     temp = a[j];
//                     a[j] = a[j+1];
//                     a[j+1]= temp;
//                 }
//             }
//         }
//         for(i =0; i<n; i++){
//             printf("%d", a[i]);
//         }
//             printf("\nchild process completed:\n");
            
        
//     }
//         else if(pid > 0)
//          {
//         wait(NULL);

//         printf("\nParent process sorting in descending order:\n");

//         for(i = 0; i< n; i++){
//             for(j=0; j<n-i-1; j++){
//                 if(a[j]<a[j+1])
//                 {
//                     temp= a[j];
//                     a[j] = a[j+1];
//                     a[j+1] = temp;
                    
//                 }
//             }
//         }
//         for(i = 0; i<n; i++){
//             printf("%d", a[i]);
//         }
//             printf("\nParent process completed.\n");
            
        
//          }
//         else
//     {
//         printf("\nFork is failde\n");
//     }

//       return 0;

        
//     }










// //4th nd practical 


// #include <stdio.h>
// #include <pthread.h>
// #include <semaphore.h>
// #include <unistd.h>

// #define N 5

// sem_t fork_sem[N];
// sem_t room;

// void *philosopher(void *arg)
// {
//     int id = *(int *)arg;

//     printf("Philosopher %d is thinking\n", id);

//     sem_wait(&room);

//     sem_wait(&fork_sem[id]);
//     printf("Philosopher %d picked left fork\n", id);

//     sem_wait(&fork_sem[(id + 1) % N]);
//     printf("Philosopher %d picked right fork\n", id);

//     printf("Philosopher %d is eating\n", id);
//     sleep(1);

//     sem_post(&fork_sem[id]);
//     sem_post(&fork_sem[(id + 1) % N]);

//     sem_post(&room);

//     printf("Philosopher %d finished eating\n", id);

//     return NULL;
// }

// int main()
// {
//     pthread_t t[N];
//     int id[N];

//     sem_init(&room, 0, N - 1);

//     for(int i = 0; i < N; i++)
//         sem_init(&fork_sem[i], 0, 1);

//     for(int i = 0; i < N; i++)
//     {
//         id[i] = i + 1;
//         pthread_create(&t[i], NULL, philosopher, &id[i]);
//     }

//     for(int i = 0; i < N; i++)
//         pthread_join(t[i], NULL);

//     for(int i = 0; i < N; i++)
//         sem_destroy(&fork_sem[i]);

//     sem_destroy(&room);

//     return 0;
// }



// //7th practical 

// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <fcntl.h>
// #include <string.h>

// int main()
// {
//     int p1[2], p2[2];
//     char filename[100];
//     char buffer[100];
//     int fd, n;
//     pid_t pid;

//     pipe(p1);
//     pipe(p2);

//     pid = fork();

//     if(pid > 0)
//     {
//         // P

//         close(p1[0]);
//         close(p2[1]);

//         printf("Enter file name: ");
//         scanf("%99s", filename);

//         write(p1[1], filename, strlen(filename) + 1);
//         close(p1[1]);

//         printf("\nFile contents received from child:\n");

//         while((n = read(p2[0], buffer, sizeof(buffer))) > 0)
//         {
//             write(STDOUT_FILENO, buffer, n);
//         }

//         close(p2[0]);

//         wait(NULL);
//     }
//     else if(pid == 0)
//     {
//         // C

//         close(p1[1]);
//         close(p2[0]);

//         read(p1[0], filename, sizeof(filename));
//         close(p1[0]);

//         fd = open(filename, O_RDONLY);

//         if(fd < 0)
//         {
//             char msg[] = "File not found!\n";
//             write(p2[1], msg, strlen(msg));
//         }
//         else
//         {
//             while((n = read(fd, buffer, sizeof(buffer))) > 0)
//             {
//                 write(p2[1], buffer, n);
//             }

//             close(fd);
//         }

//         close(p2[1]);
//     }
//     else
//     {
//         printf("Fork failed!\n");
//     }

//     return 0;
// }




// //2nd with zombie and orphan 




// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <stdlib.h>

// void sort(int a[], int n, int order)
// {
//     int i, j, temp;

//     for(i = 0; i < n - 1; i++)
//     {
//         for(j = 0; j < n - i - 1; j++)
//         {
//             if((order == 0 && a[j] > a[j+1]) ||
//                (order == 1 && a[j] < a[j+1]))
//             {
//                 temp = a[j];
//                 a[j] = a[j+1];
//                 a[j+1] = temp;
//             }
//         }
//     }
// }

// int main()
// {
//     int a[100], n, i;
//     pid_t pid;

//     printf("Enter number of elements: ");
//     scanf("%d", &n);

//     printf("Enter elements: ");
//     for(i = 0; i < n; i++)
//         scanf("%d", &a[i]);

//     pid = fork();

//     if(pid == 0)
//     {
//         sort(a, n, 0);

//         printf("\nChild process - Ascending order: ");
//         for(i = 0; i < n; i++)
//             printf("%d ", a[i]);

//         printf("\n");
//         exit(0);
//     }
//     else if(pid > 0)
//     {
//         wait(NULL);

//         sort(a, n, 1);

//         printf("Parent process - Descending order: ");
//         for(i = 0; i < n; i++)
//             printf("%d ", a[i]);

//         printf("\n");
//     }
//     else
//     {
//         printf("Fork failed!\n");
//         return 1;
//     }

//     // ZOMBIE PROCESS
//     printf("\n--- Zombie Process Demonstration ---\n");

//     pid = fork();

//     if(pid == 0)
//     {
//         printf("Child process is exiting.\n");
//         exit(0);
//     }
//     else if(pid > 0)
//     {
//         printf("Parent sleeping for 10 seconds. Child PID: %d\n", pid);
//         sleep(10);
//         wait(NULL);
//         printf("Parent collected child status. Zombie removed.\n");
//     }

//     // ORPHAN PROCESS
//     printf("\n--- Orphan Process Demonstration ---\n");

//     pid = fork();

//     if(pid == 0)
//     {
//         sleep(3);
//         printf("Child is now orphan. New Parent PID: %d\n", getppid());
//     }
//     else if(pid > 0)
//     {
//         printf("Parent process is exiting.\n");
//         exit(0);
//     }

//     return 0;
// }



        
    
        
