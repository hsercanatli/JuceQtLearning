#pragma once

#include "../Models/GainModel.h"

#include <QObject>


class GainController : public QObject {
    Q_OBJECT

public:
    explicit GainController(std::shared_ptr<GainModel> gainModel)
        : mGainModel(gainModel) {}

    Q_INVOKABLE void updateGain(qreal gain) {
        mGainModel->updateGain(gain);
    }

    Q_INVOKABLE void updateBypass(bool bypass) {
        mGainModel->updateBypass(bypass);
    }

private:
    std::shared_ptr<GainModel> mGainModel;

    Q_DISABLE_COPY_MOVE(GainController)
};