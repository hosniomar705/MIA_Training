import numpy as np
import pylab as plt
import pandas as pd


df = pd.read_csv("shrink_ray_dataset.csv")
x = df["Power"].to_numpy()
y = df["Shrinkage"].to_numpy()


class Linear_Regression_model:

    def cost_fn(self):
        m = self.y.shape[0]
        error = np.sum(((self.w*self.x+self.b)-self.y)**2)
        j = error/(2*m)
        return j
    
    def gradiant_decent(self):
        m = self.y.shape[0]
        dj_dw = np.dot(((self.w*self.x+self.b)-self.y),self.x)
        dj_db = np.sum((self.w*self.x+self.b)-self.y)
        dj_dw /= m 
        dj_db /= m
        return dj_dw,dj_db
    
    def train(self,x,y,w=0,b=0,alpha=.00001,num_of_iterations=1000):
        self.x = x
        self.y = y
        self.w = w
        self.b = b
        for i in range(num_of_iterations):
            dj_dw,dj_db = self.gradiant_decent()
            self.w = self.w - alpha*dj_dw
            self.b = self.b - alpha*dj_db

    def predict(self,x):
        y = self.w*x+self.b
        return y
    
    def predictx(self,y):
        x = (y-self.b)/self.w
        return x

test = Linear_Regression_model()
test.train(x,y)
print(f"cost_fun = {test.cost_fn()}")

plt.scatter(x,y,color="red")
plt.plot(x,test.predict(x))
plt.title("Linear_Regression_model")
plt.xlabel("Power (MW)")
plt.ylabel("Percentage (%)")
plt.grid()
plt.show()

z = 85
print(f"knob value = {test.predictx(z)}")








