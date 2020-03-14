from enum import Enum

from PySide2.QtCore import QObject, Signal

SimulationState = Enum('SimulationState', 'playing paused')


def clamp(v, smallest, largest):
    "limit value on both sides"
    return max(smallest, min(v, largest))


class AnimationControl(QObject):
    stepChanged = Signal(int)
    stateChanged = Signal(object)

    def __init__(self, solution, parent=None):
        super().__init__(parent)

        self.solution = solution
        self.freeze_time = 0
        self.current_action = self.play_action
        self.float_step = 0
        self._step = 0
        self.rewind_to_step = 0

    @property
    def step(self):
        return self._step

    @step.setter
    def step(self, value):
        self._step = value
        self.stepChanged.emit(self._step)

    # public methods:

    def play_or_pause(self):
        if self.current_action == self.pause_action:
            self.current_action = self.play_action
            self.stateChanged.emit(SimulationState.playing)
        else:
            self.pause()

    def pause(self):
        self.current_action = self.pause_action
        self.stateChanged.emit(SimulationState.paused)

    def rewind_forward(self):
        if self.solution.error:
            return

        if self.step < self.solution.number_of_steps - 1:
            self.current_action = self.rewind_forward_action

    def rewind_backward(self):
        if self.solution.error:
            return

        if self.step != 0 or self.solution.ants_at_step(0, -1) == False:
            if self.float_step - self.step > 0.05:
                self.rewind_to_step = clamp(
                    self.step, 0, self.solution.number_of_steps - 1)
            else:
                self.rewind_to_step = clamp(
                    self.step - 1, 0, self.solution.number_of_steps - 1)

            self.current_action = self.rewind_backward_action

    def update(self):
        if self.solution.error:
            return

        self.current_action()

    # private methods:
    def play_action(self):
        if self.freeze_time != 0:
            self.freeze_time -= 1
            return

        self.float_step += 1/80
        self.solution.set_step(self.float_step)

        # determinte integral step change eg 0.9 to 1.02
        # to freeze for a little in rooms
        if self.solution.ants_at_step(self.step + 1):
            self.freeze_time = 20
            self.step += 1
            self.solution.set_step(self.step)

        if self.step > self.solution.number_of_steps - 1:
            self.solution.move_ants_to_start()
            self.float_step = 0
            self.step = 0

    def pause_action(self):
        return

    def rewind_forward_action(self):
        self.float_step += 1/20
        self.solution.set_step(self.float_step)

        if self.solution.ants_at_step(self.step + 1, +1):
            self.step += 1
            self.solution.set_step(self.step)
            self.pause()

    def rewind_backward_action(self):
        self.float_step -= 1/20
        self.solution.set_step(self.float_step)

        if self.solution.ants_at_step(self.rewind_to_step, -1):
            self.step = self.rewind_to_step
            self.solution.set_step(self.step)
            self.pause()
