# used the base code from geeksforgeeks
import sys
from wordcloud import WordCloud
import matplotlib.pyplot as plt
from matplotlib.colors import LinearSegmentedColormap

def generate_wordcloud(file_path):
    word_freq = {}

    # Read the file and parse words and frequencies
    with open(file_path, 'r') as file:
        for line in file:
            if line.strip():
                word, freq = line.strip().split()
                word_freq[word] = int(freq)

    colormap = 'plasma'

    # Generate the word cloud
    wordcloud = WordCloud(width=800, height=400, background_color='white', colormap=colormap).generate_from_frequencies(word_freq)

    # Display the word cloud
    plt.figure(figsize=(10, 5))
    plt.imshow(wordcloud, interpolation='bilinear')
    plt.axis('off')
    plt.savefig('wordcloud.png') # Save the word cloud image
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python wordCloud.py <file_path>")
        sys.exit(1)

    generate_wordcloud(sys.argv[1])