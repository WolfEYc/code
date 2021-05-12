from sklearn import svm
from sklearn.neural_network import MLPClassifier
from sklearn.model_selection import train_test_split
from sklearn.model_selection import cross_validate
from sklearn.model_selection import cross_val_predict
from sklearn.metrics import classification_report
import pandas as pd
import numpy as np
from matplotlib import pyplot as plt

df = pd.read_csv('heart.csv')

dead_df = df[df['DEATH_EVENT']==1][0:300]
alive_df = df[df['DEATH_EVENT']==0][0:300]

axes = dead_df.plot(kind='scatter', x='ejection_fraction', y='serum_creatinine',color='red', label='dead patients')
alive_df.plot(kind='scatter', x='ejection_fraction', y='serum_creatinine',color='blue', label='alive patients', ax=axes)

df.columns
feature_df = df[['ejection_fraction','serum_creatinine']]

X = np.asarray(feature_df)
y = np.asarray(df['DEATH_EVENT'])

X_train, X_test, y_train, y_test = train_test_split(X,y,test_size=0.2,random_state=5)

linear_svc = svm.SVC(kernel='linear',random_state=1).fit(X_train,y_train)
rbf_svc = svm.SVC(kernel='rbf',random_state=2).fit(X_train,y_train)
relu_MLP = MLPClassifier(activation='relu',max_iter=3000,random_state=3).fit(X_train,y_train)
tanh_MLP = MLPClassifier(activation='tanh',max_iter=3000,random_state=4).fit(X_train,y_train)

linear_cv10 = cross_validate(linear_svc,X_test,y=y_test,cv=10)
rbf_cv10 = cross_validate(rbf_svc,X_test,y=y_test,cv=10)
relu_cv10 = cross_validate(relu_MLP,X_test,y=y_test,cv=10)
tanh_cv10 = cross_validate(tanh_MLP,X_test,y=y_test,cv=10)

linear_y_pred = cross_val_predict(linear_svc,X_test,y=y_test,cv=10)
rbf_y_pred = cross_val_predict(rbf_svc,X_test,y=y_test,cv=10)
relu_y_pred = cross_val_predict(relu_MLP,X_test,y=y_test,cv=10)
tanh_y_pred = cross_val_predict(tanh_MLP,X_test,y=y_test,cv=10)

linear_report = classification_report(y_test,linear_y_pred)
rbf_report = classification_report(y_test,rbf_y_pred)
relu_report = classification_report(y_test,relu_y_pred)
tanh_report = classification_report(y_test,tanh_y_pred)

xlim = axes.get_xlim()
ylim = axes.get_ylim()
x = np.linspace(xlim[0], xlim[1], 30)
y = np.linspace(ylim[0], ylim[1], 30)
Y, X = np.meshgrid(y, x)
xy = np.vstack([X.ravel(), Y.ravel()]).T
L = linear_svc.decision_function(xy).reshape(X.shape)
Rbf = rbf_svc.decision_function(xy).reshape(X.shape)

axes.contour(X, Y, L, colors='grey',
               levels=[-1, 0, 1], alpha=0.5,
               linestyles=['--', '-', '--'])

axes.contour(X, Y, Rbf, colors='purple',
               levels=[-1, 0, 1], alpha=0.5,
               linestyles=['--', '-', '--'])

print('\nLinear Kernel')
print('accuracy:',int(100*np.mean(linear_cv10['test_score'])),'%')
print(linear_report)

print('\nRBF Kernel')
print('accuracy:',int(100*np.mean(rbf_cv10['test_score'])),'%')
print(rbf_report)

print('\nRelu MLP')
print('accuracy:',int(100*np.mean(relu_cv10['test_score'])),'%')
print(relu_report)

print('\nTanh MLP')
print('accuracy:',int(100*np.mean(tanh_cv10['test_score'])),'%')
print(tanh_report)

plt.show()
