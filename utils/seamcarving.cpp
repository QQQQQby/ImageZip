#include "seamcarving.h"

#include <QDebug>

int *SeamCarving::findHorizontalSeam(QImage *image) {
    int *ans = new int[image->width()];
    if (image->height() <= 2) {
        for (int x = 0; x < image->width(); ++x)
            ans[x] = 0;
        return ans;
    }

    double **dp = new double *[image->width()];
    for (int i = 0; i < image->width(); ++i)
        dp[i] = new double[image->height()];

    for (int y = 0; y < image->height(); ++y)
        dp[0][y] = BORDER_ENERGY;

    for (int x = 1; x < image->width(); ++x) {
        for (int y = 1; y < image->height() - 1; ++y)
            dp[x][y] = fmin(fmin(dp[x - 1][y - 1], dp[x - 1][y]), dp[x - 1][y + 1]) + energy(image, x, y);
        dp[x][0] = fmin(dp[x - 1][0], dp[x - 1][1]) + BORDER_ENERGY;
        dp[x][image->height() - 1] =
                fmin(dp[x - 1][image->height() - 1], dp[x - 1][image->height() - 2]) + BORDER_ENERGY;
    }

    double min = dp[image->width() - 1][1];
    int minY = 1;
    for (int y = 2; y < image->height() - 1; ++y) {
        if (min > dp[image->width() - 1][y]) {
            min = dp[image->width() - 1][y];
            minY = y;
        }
    }

    ans[image->width() - 1] = minY;

    for (int x = image->width() - 2; x >= 0; --x) {
        min = DBL_MAX;
        for (int y = ans[x + 1] - 1; y <= ans[x + 1] + 1; ++y) {
            if (min > dp[x][y]) {
                min = dp[x][y];
                minY = y;
            }
            ans[x] = minY;
        }
    }
    for (int i = 0; i < image->width(); ++i)
        delete[] dp[i];
    delete[] dp;
    return ans;
}

int *SeamCarving::findVerticalSeam(QImage *image) {
    int *ans = new int[image->height()];
    if (image->width() <= 2) {
        for (int y = 0; y < image->height(); ++y)
            ans[y] = 0;
        return ans;
    }

    double **dp = new double *[image->width()];
    for (int i = 0; i < image->width(); ++i)
        dp[i] = new double[image->height()];

    for (int x = 0; x < image->width(); ++x)
        dp[x][0] = BORDER_ENERGY;

    for (int y = 1; y < image->height(); ++y) {
        for (int x = 1; x < image->width() - 1; ++x)
            dp[x][y] = fmin(fmin(dp[x - 1][y - 1], dp[x][y - 1]), dp[x + 1][y - 1]) + energy(image, x, y);
        dp[0][y] = fmin(dp[0][y - 1], dp[1][y - 1]) + BORDER_ENERGY;
        dp[image->width() - 1][y] =
                fmin(dp[image->width() - 1][y - 1], dp[image->width() - 2][y - 1]) + BORDER_ENERGY;
    }

    double min = dp[1][image->height() - 1];
    int minX = 1;
    for (int x = 2; x < image->width() - 1; ++x) {
        if (min > dp[x][image->height() - 1]) {
            min = dp[x][image->height() - 1];
            minX = x;
        }
    }

    ans[image->height() - 1] = minX;

    for (int y = image->height() - 2; y >= 0; --y) {
        min = DBL_MAX;
        for (int x = ans[y + 1] - 1; x <= ans[y + 1] + 1; ++x) {
            if (min > dp[x][y]) {
                min = dp[x][y];
                minX = x;
            }
            ans[y] = minX;
        }
    }
    for (int i = 0; i < image->width(); ++i)
        delete[] dp[i];
    delete[] dp;
    return ans;
}

QImage SeamCarving::removeHorizontalSeam(QImage *image, int *seam){
    QImage result = image->copy(0, 0, image->width(), image->height() - 1);
    for(int x = 0; x < image->width(); ++x)
        for(int y = seam[x] + 1; y < image->height(); ++y)
            result.setPixel(x, y - 1, image->pixel(x, y));
    return result;
}

QImage SeamCarving::removeVerticalSeam(QImage *image, int *seam){
    QImage result = image->copy(0, 0, image->width() - 1, image->height());
    for(int y = 0; y < image->height(); ++y)
        for(int x = seam[y] + 1; x < image->width(); ++x)
            result.setPixel(x - 1, y, image->pixel(x, y));
    return result;
}

double SeamCarving::energy(QImage *image, int x, int y) {
    if (x == 0 || x == image->width() - 1 || y == 0 || y == image->height() - 1)
        return BORDER_ENERGY;
    QRgb upColor = image->pixel(x, y - 1), downColor = image->pixel(x, y + 1),
            leftColor = image->pixel(x - 1, y), rightColor = image->pixel(x + 1, y);
    double rx = qRed(rightColor) - qRed(leftColor), gx = qGreen(rightColor) - qGreen(leftColor),
            bx = qBlue(rightColor) - qBlue(leftColor), ry = qRed(upColor) - qRed(downColor),
            gy = qGreen(upColor) - qGreen(downColor), by = qBlue(upColor) - qBlue(downColor);
    return sqrt(rx * rx + gx * gx + bx * bx + ry * ry + gy * gy + by * by);
}
