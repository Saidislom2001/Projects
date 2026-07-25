# Handwriting Recognition with CNNs

A convolutional neural network that recognizes handwritten digits (0–9) from the MNIST dataset, built in Jupyter Notebook with TensorFlow/Keras.

## Project structure

```
handwriting-cnn/
├── notebooks/
│   └── handwriting_cnn.ipynb   # main notebook
├── models/                     # saved trained model(s)
├── requirements.txt
├── .gitignore
└── README.md
```

## Dataset

[MNIST](http://yann.lecun.com/exdb/mnist/) — 70,000 grayscale 28x28 images of handwritten digits (60,000 train / 10,000 test). Loaded directly via `tensorflow.keras.datasets.mnist`, no manual download needed.

## Setup (WSL)

```bash
cd ~/Deep Learning/handwriting-cnn        
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
jupyter notebook --no-browser
```

Then open the printed `localhost` URL, or connect from VS Code / your browser.

## Model

A simple CNN: stacked Conv2D + MaxPooling blocks, followed by Dense layers with dropout, trained with Adam and categorical cross-entropy.

## Results

_Fill in after training:_

- Test accuracy: `98.75%`
- Training time: `TBD`

## Author

Saidislom