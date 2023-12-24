#pragma once

#include "../Models/GainModel.h"

#include <QObject>


class GainController : public QObject {
    Q_OBJECT

public:
    explicit GainController(std::shared_ptr<GainModel> gainModel)
        : mGainModel(gainModel) {}

    Q_INVOKABLE void updateGain(qreal gain);

    Q_INVOKABLE void updateBypass(bool bypass);

private:
    std::shared_ptr<GainModel> mGainModel;

    Q_DISABLE_COPY_MOVE(GainController)
};