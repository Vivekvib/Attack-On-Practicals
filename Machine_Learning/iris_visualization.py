import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# --- Load the Iris Dataset ---
# We can conveniently load it directly from seaborn
print("Loading Iris dataset...")
df = sns.load_dataset('iris')

# --- a. Plot bar chart: frequency of each class label ---
print("\nCreating frequency bar chart...")
species_counts = df['species'].value_counts()
plt.figure(figsize=(8, 6))  # Adjust figure size for better visibility
sns.barplot(x=species_counts.index, y=species_counts.values, hue=species_counts.index, legend=False)
plt.title('Frequency of Iris Species')
plt.xlabel('Species')
plt.ylabel('Count')
plt.show()

# --- b. Draw a scatter plot: Petal width vs sepal width ---
print("\nCreating scatter plot (Petal width vs Sepal width)...")
plt.figure(figsize=(10, 8))
# Use hue to color points by species for better legend
sns.scatterplot(x='petal_width', y='sepal_width', hue='species', data=df)
plt.title('Sepal Width vs Petal Width by Species')
plt.xlabel('Petal Width (cm)')
plt.ylabel('Sepal Width (cm)')
# Seaborn handles the legend automatically with 'hue'
plt.show()

# --- c. Use a pair plot: pairwise bivariate distribution ---
print("\nCreating pair plot...")
# Pair plot shows scatter plots for all numerical variables, colored by species
# Diagonals show the univariate distributions (kernel density estimates by default)
sns.pairplot(df, hue='species')
plt.suptitle('Pairwise Bivariate Distributions in the Iris Dataset', y=1.02) # y parameter adjusts title position
plt.show()